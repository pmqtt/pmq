//
// Created by pmqtt on 03.12.19.
//

#ifndef PMQ_TRANSFORMATION_IDENTITY_HPP
#define PMQ_TRANSFORMATION_IDENTITY_HPP

#include "transformation_module.hpp"

namespace pmq{
    struct transformation_identity : public transformation{
        transformation_identity() = default;
        ~transformation_identity() override = default;
        std::string transform(const std::string & msg) override {
            return msg;
        }
    };
}

#endif //PMQ_TRANSFORMATION_IDENTITY_HPP
