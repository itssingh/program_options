#include <boost/program_options.hpp>
#include <exception>
#include <iostream>
#include <cstdlib>

using namespace std;
namespace po = boost::program_options;


struct Clioption { 
  string mor;
  string eve;
  int num;
  int t=0x0;
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
    } 
     if (vm.count("mor")) {
      clioption.mor = vm["mor"].as<string>();
      clioption.t |= 0x1; // 1
    } 
     if (vm.count("eve")) {
      clioption.eve = vm["eve"].as<string>();
      clioption.t |= 0x2;// 10
    } 
     if (vm.count("num")) {
      clioption.num = vm["num"].as<int>();
      clioption.t |= 0x4;// 100
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
  if (parse_command_line(argc, argv, clioption)) { // 101
    if (clioption.t & 0x1) {
      cout << "Good Morning " << clioption.mor << "\n";
    }
    if (clioption.t & 0x2) {
      cout << "Good Evening " << clioption.eve << "\n";
    }

    if (clioption.t & 0x4) {
      cout << "Number is: " << clioption.num << "\n";
    }

  } else {
    cout << "Parsing failed!";
    exit(EXIT_FAILURE);
  }
  return 0;
}
// -n val
// --num val
// --num=val
// -nval
