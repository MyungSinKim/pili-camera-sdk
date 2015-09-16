//
//  pili_type.h
//  pili-camera-sdk
//
//  Created on 15/3/31.
//  Copyright (c) Pili Engineering, Qiniu Inc. All rights reserved.
//

#ifndef __PILI_CAMERA_SDK__TYPE__
#define __PILI_CAMERA_SDK__TYPE__

#include "pili_macro.h"
#include "flv.h"
#include "librtmp/rtmp.h"

#define PILI_STREAM_DROP_FRAME_POLICY_RANDOM        (0x00)

#define PILI_STREAM_BUFFER_TIME_INTERVAL_DEFAULT    3

PILI_TYPE_POINTER(struct pili_packet_queue, pili_packet_queue_p);

PILI_TYPE(struct pili_stream_context, pili_stream_context_t);
PILI_TYPE_POINTER(struct pili_stream_context, pili_stream_context_p);

PILI_TYPE(struct pili_h264_nalu, pili_h264_nalu_t);
PILI_TYPE_POINTER(struct pili_h264_nalu, pili_h264_nalu_p);

PILI_TYPE(struct pili_h264_key_frame, pili_h264_key_frame_t);
PILI_TYPE_POINTER(struct pili_h264_key_frame, pili_h264_key_frame_p);

PILI_TYPE(struct pili_error, pili_error_t);
PILI_TYPE(enum pili_error_code, pili_error_code_t);

#define PILI_STREAM_STATE_UNKNOW        0x00
#define PILI_STREAM_STATE_CONNECTING    0x01
#define PILI_STREAM_STATE_CONNECTED     0x02
#define PILI_STREAM_STATE_DISCONNECTED  0x03
#define PILI_STREAM_STATE_ERROR         0x04

typedef void (*pili_stream_state_cb)(uint8_t state, pili_error_t error);

/**
 * stream context
 */
pili_stream_context_p pili_create_stream_context();
int pili_init_stream_context(pili_stream_context_p ctx,
                             uint8_t drop_frame_policy,
                             uint32_t buffer_time_interval,
                             pili_stream_state_cb stream_state_cb);
int pili_release_stream_context(pili_stream_context_p ctx);

struct pili_stream_context {
    char                    *push_url;
    RTMP                    *rtmp;
    pili_packet_queue_p     queue;
    uint8_t                 drop_frame_policy;
    uint32_t                buffer_time_interval;
    pili_stream_state_cb    stream_state_cb;
    int                     state;
};

/**
 * h264
 */
struct pili_h264_nalu {
    uint8_t *data;
    size_t  length;
};

// Set nalu's length to -1 if there's no such nalu.
struct pili_h264_key_frame {
    pili_h264_nalu_t sps;
    pili_h264_nalu_t pps;
    pili_h264_nalu_t sei;
    pili_h264_nalu_t idr;
};

/**
 * error
 */
enum pili_error_code {
    pili_ok = 0,
    pili_connect_failure,
    pili_connect_stream_failure,
    pili_rtmp_close_func_invoked,
};

struct pili_error {
    pili_error_code_t     code;
    char                  msg[1024];
};

char *pili_version();

#endif  // __PILI_CAMERA_SDK__TYPE__
