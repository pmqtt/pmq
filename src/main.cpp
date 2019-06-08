#include <boost/log/trivial.hpp>
#include <boost/log/common.hpp>
#include <boost/log/sinks.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/program_options.hpp>
#include <boost/shared_ptr.hpp>
#include <iostream>

#include "header/null_deleter.hpp"
#include "header/PMQConfigure.hpp"
#include "header/security.hpp"
#include "header/server.hpp"
#include "header/startup_configuration.hpp"




pmq::config parse_program_options(int argc,char **argv){
    boost::program_options::options_description desc{"Options"};
    desc.add_options()
            ("help,h", "Help screen")
            ("version,v", "print version")
            ("port,p", boost::program_options::value<int>()->default_value(1883) ,"port");

    boost::program_options::variables_map vm;
    store(parse_command_line(argc, argv, desc), vm);
    notify(vm);

    if (vm.count("help")) {
        std::cout << desc << '\n';
        exit(0);
    }
    if (vm.count("version")) {
        std::cout << "PMQ 2019 - v" << VERSION <<" - " <<std::endl;
        exit(0);
    }
    pmq::config conf;
    if(vm.count("port")){
        conf.setPort(vm["port"].as<int>());
    }
    return conf;
}


int main(int argc,char **argv,char **envp){

    pmq::config conf = parse_program_options(argc,argv);
    BOOST_LOG_TRIVIAL(info)<<"Start PMQ "<<VERSION;
    pmq::ring_zero::clean_argv(argc,&argv);
    pmq::ring_zero::clean_environment(&envp);


    pmq::server server(conf.get_port());
    server.run();

    return 0;
}