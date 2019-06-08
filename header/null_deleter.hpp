
#ifndef PMQ_NULL_DELETER_HPP
#define PMQ_NULL_DELETER_HPP

namespace pmq::detail{
    struct null_deleter
    {
        //! Function object result type
        typedef void result_type;
        /*!
         * Does nothing
         */
        template< typename T >
        void operator() (T*) const {}
    };

}

#endif //PMQ_NULL_DELETER_HPP
