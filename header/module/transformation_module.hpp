//
// Created by pmqtt on 23.11.19.
//

#ifndef PMQ_TRANSFORMATION_MODULE_HPP
#define PMQ_TRANSFORMATION_MODULE_HPP

namespace pmq{
    class tranformation_module{
    public:
        tranformation_module() = default;
        ~tranformation_module() = default;

        std::string transform(const std::shared_ptr<transformation> & process,const std::string &msg);

    };
}

#endif //PMQ_TRANSFORMATION_MODULE_HPP
