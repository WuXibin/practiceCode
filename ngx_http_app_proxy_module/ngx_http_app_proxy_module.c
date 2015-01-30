#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>

static char *ngx_http_app_proxy(ngx_conf_t *cf, ngx_command_t *cmd, void *conf);
static void *ngx_http_app_proxy_create_loc_conf(ngx_conf_t *cf);
static char *ngx_http_app_proxy_merge_loc_conf(ngx_conf_t *cf, void *prev, void *conf);
static ngx_int_t app_proxy_upstream_create_request(ngx_http_request_t *r);
static ngx_int_t app_proxy_upstream_status_line(ngx_http_request_t *r);
static ngx_int_t app_proxy_upstream_process_header(ngx_http_request_t *r);
static ngx_int_t app_proxy_upstream_finalize_request(ngx_http_request_t *r, ngx_int_t rc);

typedef struct {
    ngx_http_upstream_conf_t upstream;
} ngx_http_app_proxy_conf_t;

typedef struct {
    ngx_http_status_t status;
} ngx_http_app_proxy_ctx_t;

static ngx_command_t ngx_http_app_proxy_commands[] = {
    {
        ngx_string("upstream_conn_timeout"),
        NGX_HTTP_LOC_CONF | NGX_CONF_TAKE1,
        ngx_conf_set_msec_slot,
        NGX_HTTP_LOC_CONF_OFFSET,
        offsetof(ngx_http_app_proxy_conf_t, upstream.connect_timeout),
        NULL
    },
    {
        ngx_string("upstream_send_timeout"),
        NGX_HTTP_LOC_CONF | NGX_CONF_TAKE1,
        ngx_conf_set_msec_slot,
        NGX_HTTP_LOC_CONF_OFFSET,
        offsetof(ngx_http_app_proxy_conf_t, upstream.send_timeout),
        NULL
    },
    {
        ngx_string("upstream_read_timeout"),
        NGX_HTTP_LOC_CONF | NGX_CONF_TAKE1,
        ngx_conf_set_msec_slot,
        NGX_HTTP_LOC_CONF_OFFSET,
        offsetof(ngx_http_app_proxy_conf_t, upstream.read_timeout),
        NULL
    },
    {
        ngx_string("app_proxy"), 
        NGX_HTTP_LOC_CONF | NGX_CONF_NOARGS,
        ngx_http_app_proxy, 
        NGX_HTTP_LOC_CONF_OFFSET,
        0,
        NULL
    },
    ngx_null_command
};

static ngx_http_module_t ngx_http_app_proxy_ctx = {
    NULL,
    NULL,

    NULL,
    NULL,

    NULL,
    NULL,

    ngx_http_app_proxy_create_loc_conf,
    ngx_http_app_proxy_merge_loc_conf
};

ngx_module_t ngx_http_app_proxy_module = {
    NGX_MODULE_V1,
    &ngx_http_app_proxy_ctx,
    ngx_http_app_proxy_commands,
    NGX_HTTP_MODULE,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NGX_MODULE_V1_PADDING
};

static void *ngx_http_app_proxy_create_loc_conf(ngx_conf_t *cf) {
    ngx_http_app_proxy_conf_t *apcf;
    apcf = ngx_palloc(cf->pool, sizeof(ngx_http_app_proxy_conf_t));
    if(apcf == NULL) {
        return NULL;
    }

    apcf->upstream.connect_timeout = NGX_CONF_UNSET_MSEC;
    apcf->upstream.send_timeout = NGX_CONF_UNSET_MSEC;
    apcf->upstream.read_timeout = NGX_CONF_UNSET_MSEC;
    apcf->upstream.hide_headers = NGX_CONF_UNSET_PTR;
    apcf->upstream.pass_headers = NGX_CONF_UNSET_PTR;

    return apcf;
}

static char *ngx_http_app_proxy_merge_loc_conf(ngx_conf_t *cf, void *prev, void *conf) {
    ngx_http_app_proxy_conf_t *parent = prev;
    ngx_http_app_proxy_conf_t *child = conf;
    
    ngx_conf_merge_msec_value(parent->upstream.connect_timeout, child->upstream.connect_timeout, 500);
    ngx_conf_merge_msec_value(parent->upstream.send_timeout, child->upstream.send_timeout, 500);
    ngx_conf_merge_msec_value(parent->upstream.read_timeout, child->upstream.read_timeout, 500);

    ngx_hash_init_t hash;
    hash.max_size = 100;
    hash.bucket_size = 1024;
    hash.name = "app_proxy_header_hash";
    if(ngx_http_upstream_hide_headers_hash(cf, &child->upstream, &parent->upstream, 
                ngx_http_proxy_hide_headers, &hash) != NGX_OK) {
        return NGX_CONF_ERR; 
    }

    return NGX_CONF_OK;
}

static ngx_int_t ngx_http_app_proxy_handler(ngx_http_request_t *r) {
    if(!(r->method & (NGX_HTTP_GET | NGX_HTTP_HEAD))) {
        return NGX_HTTP_NOT_ALLOWED;
    }

    ngx_int_t rc = ngx_http_discard_request_body(r);
    if(rc != NGX_OK) {
        return rc;
    }

    ngx_buf_t *b;
    ngx_chain_t out[2];

    ngx_str_t response = ngx_string("Hello World!");
    b = ngx_create_temp_buf(r->pool, response.len);
    if(b == NULL) {
        return NGX_HTTP_INTERNAL_SERVER_ERROR;
    }

    ngx_memcpy(b->pos, response.data, response.len);
    b->last = b->pos + response.len;
    b->last_buf = 0;
    
    out[0].buf = b;
    out[0].next = &out[1];

    ngx_http_app_proxy_conf_t *apcf = ngx_http_get_module_loc_conf(r, ngx_http_app_proxy_module);
    if(apcf == NULL) {
        ngx_log_error(NGX_LOG_ERR, r->connection->log, 0, "ngx_http_conf_get_module_loc_conf error");
        return NGX_HTTP_INTERNAL_SERVER_ERROR;
    }

    b = ngx_create_temp_buf(r->pool, 128);
    if(b == NULL) {
        return NGX_HTTP_INTERNAL_SERVER_ERROR;
    }
    ngx_log_error(NGX_LOG_DEBUG, r->connection->log, 0, "timeout configuration: %d %d %d", apcf->upstream.connect_timeout, 
            apcf->upstream.send_timeout, apcf->upstream.read_timeout);

    ngx_sprintf(b->pos, "%d %d %d", apcf->upstream.connect_timeout, 
            apcf->upstream.send_timeout, apcf->upstream.read_timeout);
    b->last = b->pos + ngx_strlen(b->pos);
    b->last_buf = 1;

    out[1].buf = b;
    out[1].next = NULL;

    ngx_str_t type = ngx_string("text/plain");
    r->headers_out.status = NGX_HTTP_OK;
    r->headers_out.content_type = type;
    r->headers_out.content_length_n = response.len + ngx_strlen(b->pos);

    rc = ngx_http_send_header(r);
    if(rc == NGX_ERROR || rc > NGX_OK || r->header_only) {
        return rc;
    }
    return ngx_http_output_filter(r, out);
}

static char *ngx_http_app_proxy(ngx_conf_t *cf, ngx_command_t *cmd, void *conf) {
    ngx_http_core_loc_conf_t *clcf;
    clcf = ngx_http_conf_get_module_loc_conf(cf, ngx_http_core_module);     
    clcf->handler = ngx_http_app_proxy_handler;
    return NGX_CONF_OK;
}

static ngx_int_t app_proxy_upstream_create_request(ngx_http_request_t *r) {
    static ngx_str_t backendQueryLine = ngx_string("GET /s?wd=%V HTTP/1.1\r\n"
            "Host: www.baidu.com\r\nConnection: close\r\n\r\n");
    ngx_int_t queryLineLen = backendQueryLine.len + r->args.len - 2;
    ngx_buf_t *b = ngx_create_temp_buf(r->pool, queryLineLen);
    if(b == NULL) {
        return NGX_ERROR;
    }
    b->last = b->pos + queryLineLen;
    ngx_snprintf(b->pos, queryLineLen, (char *)backendQueryLine.data, &r->args);

    r->upstream->request_bufs = ngx_alloc_chain_link(r->pool);
    if(r->upstream->request_bufs == NULL) {
        return NGX_ERROR;
    }

    r->upstream->request_bufs->buf = b;
    r->upstream->request_bufs->next = NULL;

    r->upstream->request_sent = 0;
    r->upstream->header_sent = 0;

    r->header_hash = 1;
    return NGX_OK;
}

static ngx_int_t app_proxy_upstream_status_line(ngx_http_request_t *r) {
    ngx_http_app_proxy_ctx_t *ctx = ngx_http_get_module_ctx(r, ngx_http_app_proxy_module);
    if(ctx == NULL) {
        return NGX_ERROR;
    }

    ngx_http_upstream_t *u = r->upstream;

    ngx_int_t rc = ngx_http_parse_status_line(r, &u->buffer, &ctx->status);
    if(rc == NGX_AGAIN) {
        return rc;
    }

    if(rc == NGX_ERROR) {
        ngx_log_error(NGX_LOG_ERR, r->connection->log, 0, 
                "upstream sent no valid HTTP/1.0 header");
        r->http_version = NGX_HTTP_VERSION_9;
        u->state->status = NGX_HTTP_OK;

        return NGX_OK;
    }

    if(u->state) {
        u->state->status = ctx->status.code;
    }

    u->headers_in.status_n = ctx->status.code;
    len = ctx->status.end - ctx->status.start;
    u->headers_in.status_line.len = len;
    u->headers_in.status_line.data = ngx_palloc(r->pool, len);
    if(u->headers_in.status_line.data == NULL) {
        return NGX_ERROR;
    }
    ngx_memcpy(u->headers_in.status_line.data, ctx->status.start, len);
    u->process_header = app_proxy_upstream_process_header;
    return app_proxy_upstream_process_header(r);
}

static ngx_int_t app_proxy_upstream_process_header(ngx_http_request_t *r) {
    ngx_http_upstream_main_conf_t *umcf = ngx_http_module_main_conf(r, ngx_http_upstream_module);    
    while(1) {
        ngx_int_t rc = ngx_http_parse_header_line(r, &r->upstream->buffer, 1);
        if(rc == NGX_OK) {
            ngx_table_elt_t *h = ngx_list_push(&r->upstream->headers_in.headers);
            if(h == NULL) {
                return NGX_ERROR;
            }
            h->hash = r->header_hash;
            h->key.len = r->header_name_end - r->header_name_start;
            h->value.len = r->header_end - r->header_start;
            h->key.data = ngx_palloc(r->pool, h->key.len + 1 + h->value.len + 1 + h->key.len);
            if(h->key.data == NULL) {
                return NGX_ERROR;
            }

            h->value.data = h->key.data + h->key.len + 1;
            h->lowcase_key = h->key.data + h->key.len + 1 + h->value.len + 1;
            ngx_memcpy(h->key.data, r->header_name_start, h->value.len);
            h->key.data[h->key.len] = '\0';
            ngx_memcpy(h->value.data, r->header_size, h->value.len);
            h->value.data[h->value.len] = '\0';

            if(h->key.len == r->lowcase_index) {
                ngx_memcpy(h->lowcase_key, r->lowcase_header, h->key.len);
            } else {
                ngx_strlow(h->lowcase_key, h->key.data, h->key.len);
            }

            ngx_http_upstream_header_t *hh = ngx_hash_find(&umcf->headers_in_hash,
                    h->hash, h->lowcase_key, h->key.len);
            if(hh && hh->handler(r, h, hh->offset) != NGX_OK) {
                return NGX_ERROR;
            }

            continue;
        }

        if(rc == NGX_HTTP_PARSE_HEADER_DONE) {
            if(r->upstream->headers_in.server == NULL) {
                ngx_table_elt_t *h = ngx_list_push(&r->upstream->headers_in.headers);
                if(h == NULL) {
                    return NGX_ERROR;
                }

                h->hash = ngx_hash(ngx_hash(ngx_hash(
                                ngx_hash(ngx_hash('s', 'e'), 'r'), 'v'), 'e'), 'r');
                
            }
        }
    }
}

static ngx_int_t app_proxy_upstream_finalize_request(ngx_http_request_t *r, ngx_int_t rc);
