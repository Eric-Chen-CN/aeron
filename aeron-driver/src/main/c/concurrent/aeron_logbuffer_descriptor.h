/*
 * Copyright 2014 - 2017 Real Logic Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef AERON_AERON_LOGBUFFER_DESCRIPTOR_H
#define AERON_AERON_LOGBUFFER_DESCRIPTOR_H

#include "util/aeron_bitutil.h"
#include "concurrent/aeron_atomic.h"

#define AERON_LOGBUFFER_PARTITION_COUNT (3)
#define AERON_LOGBUFFER_DEFAULT_FRAME_HEADER_MAX_LENGTH  (AERON_CACHE_LINE_LENGTH * 2)

#pragma pack(push)
#pragma pack(4)
typedef struct aeron_logbuffer_metadata_stct
{
    int64_t term_tail_counters[AERON_LOGBUFFER_PARTITION_COUNT];
    int32_t active_partition_index;
    uint8_t pad1[(2 * AERON_CACHE_LINE_LENGTH) - ((AERON_LOGBUFFER_PARTITION_COUNT * sizeof(int64_t)) + sizeof(int32_t))];
    int64_t time_of_last_status_message;
    int64_t end_of_stream_position;
    uint8_t pad2[(2 * AERON_CACHE_LINE_LENGTH) - (2 * sizeof(int64_t))];
    int64_t correlation_id;
    int32_t initialTerm_id;
    int32_t default_frame_header_length;
    int32_t mtu_length;
    uint8_t pad3[(AERON_CACHE_LINE_LENGTH) - (5 * sizeof(int32_t))];
}
aeron_logbuffer_metadata_t;
#pragma pack(pop)

#define AERON_LOGBUFFER_META_DATA_LENGTH (sizeof(aeron_logbuffer_metadata_t) + AERON_LOGBUFFER_DEFAULT_FRAME_HEADER_MAX_LENGTH)

#define AERON_LOGBUFFER_COMPUTE_LOG_LENGTH(term_length) ((term_length * AERON_LOGBUFFER_PARTITION_COUNT) + AERON_LOGBUFFER_META_DATA_LENGTH)

#define AERON_LOGBUFFER_GET_ACTIVE_PARTITION_INDEX(d,m) (AERON_GET_VOLATILE(d,(m->active_partition_index)))

#endif //AERON_AERON_LOGBUFFER_DESCRIPTOR_H
