/*
 * Copyright 2016 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SCOPEXIT_DEFINED
#define SCOPEXIT_DEFINED

#define MACRO_CONCAT(X, Y)              MACRO_CONCAT_IMPL_PRIV(X, Y)
#define MACRO_CONCAT_IMPL_PRIV(X, Y)    X ## Y
#define MACRO_APPEND_LINE(name)         MACRO_CONCAT(name, __LINE__)

#include <functional>

/** ScopeExit calls a std:::function<void()> in its destructor. */
class ScopeExit {
public:
    ScopeExit() = default;
    ScopeExit(std::function<void()> f) : fFn(std::move(f)) {}
    ScopeExit(ScopeExit&& that) : fFn(std::move(that.fFn)) {}

    ~ScopeExit() {
        if (fFn) {
            fFn();
        }
    }

    void clear() { fFn = {}; }

    ScopeExit& operator=(ScopeExit&& that) {
        fFn = std::move(that.fFn);
        return *this;
    }

private:
    std::function<void()> fFn;

    ScopeExit(           const ScopeExit& ) = delete;
    ScopeExit& operator=(const ScopeExit& ) = delete;
};

#define SCOPE_EXIT(stmt)                              \
    ScopeExit MACRO_APPEND_LINE(scope_exit_)([&]() { stmt; })

#endif  // SCOPEXIT_DEFINED
