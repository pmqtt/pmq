//
// Created by pmqtt on 23.11.19.
//

#ifndef PMQ_TRANSFORMATION_MODULE_HPP
#define PMQ_TRANSFORMATION_MODULE_HPP

#include <string>
namespace pmq{

    struct transformation{
        transformation()= default;
        virtual ~transformation() = default;
        virtual std::string transform(const std::string & transform) = 0;
    };

    class tranformation_module{
    public:
        tranformation_module() = default;
        ~tranformation_module() = default;

        std::string transform(const std::shared_ptr<transformation> & process,const std::string &msg){
            return process->transform(msg);
        }

    };
}

#endif //PMQ_TRANSFORMATION_MODULE_HPP
