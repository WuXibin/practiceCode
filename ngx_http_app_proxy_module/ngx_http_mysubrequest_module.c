#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>


typedef struct {
    ngx_string uri;
    ngx_string args;
    ngx_http_request_t *subr;   
} ngx_http_mysubrequest_conf_t;

typedef struct {
    ngx_array_t *subrequests;
} ngx_http_mysubrequest_ctx_t;

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

        ctx->subrequests = ngx_array_create(r->pool, 2, sizeof(ngx_http_request_t));
        if(ctx->subrequests == NULL) {
            return NGX_ERROR;
        }

        ngx_string location1 = ngx_string("/AdvertiseService/AppHandler.ashx");
        ngx_http_mysubrequest_conf_t *mycf = ngx_array_push(ctx->subrequests);
        mycf->uri.data = ngx_palloc(r->pool, location1.len);
        if(mycf->uri.data == NULL) {
            return NGX_ERROR; 
        }
        ngx_memcpy(mycf->uri.data, location1.data, location1.len);
        mycf->uri.len = location1.len;
        mycf->args = r->args;
        
        ngx_string location2 = ngx_string("/adfront/deliver");
        mycf= ngx_array_push(ctx->subrequests);
        mycf->uri.data = ngx_palloc(r->pool, location2.len);
        if(mycf->uri.data == NULL) {
            return NGX_ERROR;
        }
        ngx_memcpy(mycf->uri.data, location2.data, location2.len);
        mycf->uri.len = location2.len;
        mycf->args = r->args;

        ngx_http_set_ctx(r, ctx, ngx_http_mysubrequest_module);

        //start subrequest
        size_t i;
        for(i = 0; i < ctx->subrequests.nelts; ++i) {
            mycf = ((ngx_http_mysubrequest_conf_t *)ctx->subrequests.elts)[i];
            int flags = NGX_HTTP_SUBREQUEST_IN_MEMORY | NGX_HTTP_SUBREQUEST_WAITED;
            ngx_int_t rc = ngx_http_subrequest(r, &mycf->uri, &mycf->args, 
                    &mycf->subr, NULL, flags);

            if(rc != NGX_OK) return NGX_ERROR;
        }

        return NGX_DONE;
    }

    size_t i;
    for(i = 0; i < ctx->subrequests.nelts; ++i) {
        ngx_http_mysubrequest_conf_t *mycf = ((ngx_http_mysubrequest_conf_t *)ctx->subrequests.elts)[i];
        if(!mycf->subr->done) {
            r->main->count++;
            return NGX_DONE;
        }
    } 

    ngx_string sub_error("subrequest error!");
    ngx_chain_t out[3];
    //all subrequests have been done
    for(i = 0; i < ctx->subrequests.nelts; ++i) {
        ngx_http_mysubrequest_conf_t *mycf = ((ngx_http_mysubrequest_conf_t *)ctx->subrequests.elts)[i];
        ngx_http_request_t *subr = mycf->subr; 
        if(subr->headers_out.status == NGX_HTTP_OK) {
            out[i].b = subr->upstream->buffer;
            out[i].next = out[i+1];
        } else {
            ngx_buf_t *b = ngx_create_temp_buf(r->pool, sub_error.len);  
            ngx_memcpy(b->pos, sub_error.data, sub_error.len);
            b->last = b->pos + sub_error.len;
        }
    }

    //out[i-1].b->last_buf = 1;
    out[i-1].next = NULL;
    ngx_http_send_header(r);
    ngx_http_output_filter(r, &out);

    return NGX_OK;
}
