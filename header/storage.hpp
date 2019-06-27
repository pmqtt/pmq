//
// Created by pmqtt on 2019-06-23.
//

#ifndef PMQ_STORAGE_HPP
#define PMQ_STORAGE_HPP

namespace pmq{

    class storage{
    public:
        storage();
        virtual ~storage();
        void add_subscriber(const std::string & client_id, std::string & topic);
        void remove_subcriber(const std::string &client_id, std::string & topic);
        std::string & operator[](const std::string & topic );
    private:
    };

}

#endif //PMQ_STORAGE_HPP
