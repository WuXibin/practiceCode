#ifndef _NGX_ADUPSTREAM_STRUCT_H_INCLUDED_
#define _NGX_ADUPSTREAM_STRUCT_H_INCLUDED_

#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>
#include <sys/time.h>

typedef struct {
    ngx_http_upstream_conf_t     upstream;
    void                         *plugin;
} ngx_http_ahupstream_loc_conf_t;


typedef struct {
    ngx_http_request_t      *request;
    ngx_str_t               message;
    int                     has_processed;
    void                    *crequest;
    struct timeval          tv_begin;
    struct timeval          tv_end;
} ngx_http_ahupstream_ctx_t;

#endif //_NGX_ADUPSTREAM_STRUCT_H_INCLUDED_
