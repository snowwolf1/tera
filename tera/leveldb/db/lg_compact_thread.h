// Copyright (c) 2015, Baidu.com, Inc. All Rights Reserved
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef LEVELDB_DB_LG_COMPACT_THREAD_H_
#define LEVELDB_DB_LG_COMPACT_THREAD_H_

#include "leveldb/slice.h"
#include "util/thread.h"
#include "db/db_impl.h"

namespace leveldb {

class LGCompactThread : public Thread {
public:
    LGCompactThread(uint32_t lg_id, DBImpl* lg_impl,
                    const Slice* begin = NULL, const Slice* end = NULL,
                    bool is_miss_file = false)
        : lg_id_(lg_id), lg_impl_(lg_impl),
          begin_(begin), end_(end), is_for_missing_(is_miss_file) {}
    virtual ~LGCompactThread() {}

    virtual void Run(void* params) {
        std::cout << "LG Thread #" << lg_id_ << ": CompactRange(): "
            << (is_for_missing_?"just copy missing file":"") << std::endl;
        if (is_for_missing_) {
            lg_impl_->CompactMissFiles(begin_, end_);
        } else {
            lg_impl_->CompactRange(begin_, end_);
        }
    }

private:
    uint32_t lg_id_;
    DBImpl* lg_impl_;
    const Slice* begin_;
    const Slice* end_;
    bool is_for_missing_;
};

} // namespace leveldb

#endif // LEVELDB_DB_LG_COMPACT_THREAD_H_
