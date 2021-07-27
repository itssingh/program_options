#include <boost/program_options.hpp>
#include <exception>
#include <iostream>
#include <cstdlib>

using namespace std;
namespace po = boost::program_options;
enum dtime { MOR=1, EVE, NUM };

struct Clioption { 
  string name;
  int num;
  dtime t;
};


bool parse_command_line(int argc, char const *argv[], Clioption &clioption) {
  po::options_description desc("You can see for these options");
  desc.add_options()("help,h", "show this help")
  (
    "mor,m", boost::program_options::value<string>(),
      "shows morning greeting")("eve,e",
                                boost::program_options::value<string>(),
                                "shows evening greeting")("num,n",
                                                          boost::
                                                              program_options::
                                                                  value<int>(),
                                                          "a random integer");

  po::variables_map vm;
  try {
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);
    if (vm.count("help") > 0 || argc==1) {
      cout << desc << "\n";
      cout <<"help printed"<<"\n";
    } else if (vm.count("mor")) {
      clioption.name = vm["mor"].as<string>();
      cout <<"mor printed"<<"\n";
      clioption.t = MOR;
    } else if (vm.count("eve")) {
      clioption.name = vm["eve"].as<string>();
      clioption.t = EVE;
      cout <<"eve printed"<<"\n";
    } else if (vm.count("num")) {
      clioption.num = vm["num"].as<int>();
      clioption.t = NUM;
      cout <<"num printed"<<"\n";
    }
  } catch (boost::bad_any_cast &) {
    cout << "wrong parameter type" << endl;
    cout << desc << endl;
    return false;
  } catch (boost::program_options::error &) {
    cout << "wrong command line arguments" << endl;
    cout << desc << endl;
    return false;
  }
  return true;
}

int main(int argc, char const *argv[]) { 
    Clioption clioption;
    if(parse_command_line(argc, argv, clioption)){
        cout<<"enum val="<<clioption.t<<"\n";
        switch (clioption.t)
        {
        case MOR:
            cout<<"Good Morning "<<clioption.name<<"\n";
            break;
        case EVE:
            cout<<"Good Evening "<<clioption.name<<"\n";
            break;
        case NUM:
            cout<<"Number is: "<<clioption.num<<"\n";
            break;
        }
    }
    else{
      cout<<"Parsing failed!";
      exit(EXIT_FAILURE);
    }
    return 0; 
}

// -n val
// --num val
// --num=val
// -nval
