#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>


typedef struct {
    ngx_int_t done;
    ngx_str_t uri;
    ngx_str_t args;
    ngx_http_request_t *subr;   
} ngx_http_mysubrequest_conf_t;

typedef struct {
    ngx_array_t *subrequests;
} ngx_http_mysubrequest_ctx_t;


static char *ngx_http_mysubrequest(ngx_conf_t * cf, ngx_command_t * cmd, void * conf);
static ngx_int_t ngx_http_mysubrequest_handler(ngx_http_request_t *r);
static ngx_int_t ngx_http_mysubrequest_post_handler(ngx_http_request_t *r, void *data, ngx_int_t rc);


static ngx_command_t  ngx_http_mysubrequest_commands[] = {

    {
        ngx_string("mysubrequest"),
        NGX_HTTP_MAIN_CONF | NGX_HTTP_SRV_CONF | NGX_HTTP_LOC_CONF | NGX_HTTP_LMT_CONF | NGX_CONF_NOARGS,
        ngx_http_mysubrequest,
        NGX_HTTP_LOC_CONF_OFFSET,
        0,
        NULL
    },

    ngx_null_command
};

static ngx_http_module_t  ngx_http_mysubrequest_module_ctx = {
    NULL,                               /* preconfiguration */
    NULL,                  		/* postconfiguration */

    NULL,                               /* create main configuration */
    NULL,                               /* init main configuration */

    NULL,                               /* create server configuration */
    NULL,                               /* merge server configuration */

    NULL,       		        /* create location configuration */
    NULL         			/* merge location configuration */
};

ngx_module_t  ngx_http_mysubrequest_module = {
    NGX_MODULE_V1,
    &ngx_http_mysubrequest_module_ctx,           /* module context */
    ngx_http_mysubrequest_commands,              /* module directives */
    NGX_HTTP_MODULE,                       /* module type */
    NULL,                                  /* init master */
    NULL,                                  /* init module */
    NULL,                                  /* init process */
    NULL,                                  /* init thread */
    NULL,                                  /* exit thread */
    NULL,                                  /* exit process */
    NULL,                                  /* exit master */
    NGX_MODULE_V1_PADDING
};


static char *
ngx_http_mysubrequest(ngx_conf_t * cf, ngx_command_t * cmd, void * conf) {
    ngx_http_core_loc_conf_t  *clcf;

    clcf = ngx_http_conf_get_module_loc_conf(cf, ngx_http_core_module);

    clcf->handler = ngx_http_mysubrequest_handler;

    return NGX_CONF_OK;
}


static ngx_int_t 
ngx_http_mysubrequest_handler(ngx_http_request_t *r) {
    ngx_http_mysubrequest_ctx_t *ctx = ngx_http_get_module_ctx(r, ngx_http_mysubrequest_module);
    if(ctx == NULL) {
        ctx = ngx_palloc(r->pool, sizeof(ngx_http_mysubrequest_ctx_t));
        if(ctx == NULL) {
            return NGX_ERROR;
        }

        ctx->subrequests = ngx_array_create(r->pool, 2, sizeof(ngx_http_mysubrequest_conf_t));
        if(ctx->subrequests == NULL) {
            return NGX_ERROR;
        }
        ngx_http_set_ctx(r, ctx, ngx_http_mysubrequest_module);

        ngx_str_t location1 = ngx_string("/AdvertiseService/AppHandler.ashx");
        ngx_http_mysubrequest_conf_t *mycf = ngx_array_push(ctx->subrequests);
        mycf->uri.data = ngx_palloc(r->pool, location1.len);
        if(mycf->uri.data == NULL) {
            return NGX_ERROR; 
        }
        ngx_memcpy(mycf->uri.data, location1.data, location1.len);
        mycf->uri.len = location1.len;
        mycf->args = r->args;
        mycf->done = 0;
        
        ngx_str_t location2 = ngx_string("/adfront/deliver");
        mycf = ngx_array_push(ctx->subrequests);
        mycf->uri.data = ngx_palloc(r->pool, location2.len);
        if(mycf->uri.data == NULL) {
            return NGX_ERROR;
        }
        ngx_memcpy(mycf->uri.data, location2.data, location2.len);
        mycf->uri.len = location2.len;
        mycf->args = r->args;
        mycf->done = 0;

        //start subrequest
        size_t i;
        mycf = ctx->subrequests->elts;
        for(i = 0; i < ctx->subrequests->nelts; ++i, ++mycf) {
            int flags = NGX_HTTP_SUBREQUEST_IN_MEMORY | NGX_HTTP_SUBREQUEST_WAITED;
            ngx_http_post_subrequest_t *psr = ngx_palloc(r->pool, sizeof(ngx_http_post_subrequest_t));
            if(psr == NULL) {
                return NGX_HTTP_INTERNAL_SERVER_ERROR;
            }
            psr->handler = ngx_http_mysubrequest_post_handler;
            psr->data = mycf;

            ngx_int_t rc = ngx_http_subrequest(r, &mycf->uri, &mycf->args, 
                    &mycf->subr, psr, flags);

            if(rc != NGX_OK) return NGX_ERROR;
        }

        r->main->count++;
        return NGX_DONE;
    }

    //check if subrequests has been done
    size_t i;
    ngx_http_mysubrequest_conf_t *mycf;
    for(i = 0, mycf = ctx->subrequests->elts; i < ctx->subrequests->nelts; ++i, ++mycf) {
        //mycf = &((ngx_http_mysubrequest_conf_t *)ctx->subrequests->elts)[i];
        printf("hello world\n");
        if(!mycf->done) {
            r->main->count++;
            return NGX_DONE;
        }
    } 

    //all subrequests have been done
    ngx_str_t sub_error = ngx_string("subrequest error!");
    ngx_chain_t out[3];
    int content_length = 0;
    for(i = 0, mycf = ctx->subrequests->elts; i < ctx->subrequests->nelts; ++i, ++mycf) {
        //ngx_http_mysubrequest_conf_t *mycf = &((ngx_http_mysubrequest_conf_t *)ctx->subrequests->elts)[i];
        ngx_http_request_t *subr = mycf->subr; 
        if(subr->headers_out.status == NGX_HTTP_OK) {
            out[i].buf = &subr->upstream->buffer;
            out[i].next = &out[i+1];
        } else {
            ngx_buf_t *b = ngx_create_temp_buf(r->pool, sub_error.len);  
            ngx_memcpy(b->pos, sub_error.data, sub_error.len);
            b->last = b->pos + sub_error.len;

            out[i].buf = b;
            out[i].next = &out[i+1];
        }
        content_length += out[i].buf->last - out[i].buf->pos;
        ngx_log_debug(NGX_LOG_DEBUG, r->connection->log, 0, ">>>>>content_length: %d", content_length);
    }
    out[i-1].buf->last_buf = 1;
    out[i-1].next = NULL;

    ngx_str_t type = ngx_string("text/plain; charset=utf-8");
    r->headers_out.content_type = type;
    r->headers_out.status = NGX_HTTP_OK;
    r->headers_out.content_length_n = sub_error.len;
    r->headers_out.content_length_n = content_length;

    ngx_http_send_header(r);
    ngx_http_output_filter(r, out);

    //ngx_http_finalize_request(r, 0);

    return NGX_OK;
}


static ngx_int_t
ngx_http_mysubrequest_post_handler(ngx_http_request_t *r, void *data, ngx_int_t rc) {
    ngx_http_mysubrequest_conf_t *mycf = data;
    mycf->done = 1;
    r->parent->write_event_handler = ngx_http_core_run_phases;
    return NGX_OK;
}
