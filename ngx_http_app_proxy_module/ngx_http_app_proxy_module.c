#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>

static char *ngx_http_app_proxy(ngx_conf_t *cf, ngx_command_t *cmd, void *conf);
static void *ngx_http_app_proxy_create_loc_conf(ngx_conf_t *cf);
static char *ngx_http_app_proxy_merge_loc_conf(ngx_conf_t *cf, void *prev, void *conf);

typedef struct {
    ngx_http_upstream_conf_t upstream;
} ngx_http_app_proxy_conf_t;

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

    return apcf;
}

static char *ngx_http_app_proxy_merge_loc_conf(ngx_conf_t *cf, void *prev, void *conf) {
    ngx_http_app_proxy_conf_t *parent = prev;
    ngx_http_app_proxy_conf_t *child = conf;
    
    ngx_conf_merge_msec_value(parent->upstream.connect_timeout, child->upstream.connect_timeout, 500);
    ngx_conf_merge_msec_value(parent->upstream.send_timeout, child->upstream.send_timeout, 500);
    ngx_conf_merge_msec_value(parent->upstream.read_timeout, child->upstream.read_timeout, 500);

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

    ngx_str_t type = ngx_string("text/plain");
    ngx_str_t response = ngx_string("Hello World!");
    r->headers_out.status = NGX_HTTP_OK;
    r->headers_out.content_type = type;

    rc = ngx_http_send_header(r);
    if(rc == NGX_ERROR || rc > NGX_OK || r->header_only) {
        return rc;
    }

    ngx_buf_t *b;
    b = ngx_create_temp_buf(r->pool, response.len);
    //b = ngx_palloc(r->pool, sizeof(ngx_buf_t));
    if(b == NULL) {
        return NGX_HTTP_INTERNAL_SERVER_ERROR;
    }

    ngx_memcpy(b->pos, response.data, response.len);
    b->last = b->pos + response.len;
    b->last_buf = 1;
    
    ngx_chain_t out;
    out.buf = b;
    out.next = NULL;
    ngx_log_error(NGX_LOG_DEBUG, r->connection->log, 0, "ngx_http_output_filter");
    /*
    ngx_chain_t out[2];
    out[0].buf = b;
    out[0].next = &out[1];

    ngx_http_app_proxy_conf_t *apcf = ngx_http_conf_get_module_loc_conf(r, ngx_http_app_proxy_module);
    if(apcf == NULL) {
        ngx_log_error(NGX_LOG_ERR, r->connection->log, 0, "ngx_http_conf_get_module_loc_conf error");
        return NGX_HTTP_INTERNAL_SERVER_ERROR;
    }
    r->upstream->conf = &apcf->upstream;
    b = ngx_palloc(r->pool, 30); 
    if(b == NULL) {
        return NGX_HTTP_INTERNAL_SERVER_ERROR;
    }
    ngx_snprintf(b->pos, 30, "%d %d %d", apcf->upstream.connect_timeout, 
            apcf->upstream.send_timeout, apcf->upstream.read_timeout);
    b->last = b->pos + ngx_strlen(b->pos);
    b->last_buf = 1;
    */

    /*
    b = ngx_palloc(r->pool, sizeof(ngx_buf_t)); 
    if(b == NULL) {
        return NGX_HTTP_INTERNAL_SERVER_ERROR;
    }
    b->pos = (u_char *)" Joel";
    b->last = b->pos + sizeof(" Joel") - 1;
    out[1].buf = b;
    out[1].next = NULL;
    */

    return ngx_http_output_filter(r, &out);
}

static char *ngx_http_app_proxy(ngx_conf_t *cf, ngx_command_t *cmd, void *conf) {
    ngx_http_core_loc_conf_t *clcf;
    clcf = ngx_http_conf_get_module_loc_conf(cf, ngx_http_core_module);     
    clcf->handler = ngx_http_app_proxy_handler;
    return NGX_CONF_OK;
}
