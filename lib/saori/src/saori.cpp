#include <iostream>
#include <string>
#include <cstring>


using std::string;
using std::cout;
using std::cerr;
using std::endl;

extern "C" int load(char* h, long len){
  string txt = h;
  cout << "load: " << txt << endl;
  return 1;
};

extern "C" int unload(){
  cout << "unload" << endl;
  return 1;
};

extern "C" char* request(char* h, long *len){
  string txt = h;
  cout << "request:" << txt << endl;
  char s[7] = "Kyosan";
  string res = R"(SAORI/1.0 200 OK\r\nResult: 1\r\nValue: hello\r\nCharset: UTF-8\r\n\r\n)";
  const char* c_res = res.c_str();
  *len = (long)strlen(c_res);
  char* r_h = static_cast<char*>(malloc(*len));
  memcpy(r_h, c_res, *len);
  return r_h;
};

