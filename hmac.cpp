#include "hmac.h"
#include <string>
using std::string;

#include <cryptopp/cryptlib.h>
using CryptoPP::Exception;

#include <cryptopp/hmac.h>
using CryptoPP::HMAC;

#include <cryptopp/sha.h>
using CryptoPP::SHA256;

#include <cryptopp/base64.h>
using CryptoPP::Base64Encoder;

#include <cryptopp/filters.h>
using CryptoPP::StringSink;
using CryptoPP::StringSource;
using CryptoPP::HashFilter;

string sign(string key, string plain)
{
	string mac, encoded;

		HMAC< SHA256 > hmac((uint8_t*)key.c_str(), key.length());		

		StringSource(plain, true, 
			new HashFilter(hmac,
				new StringSink(mac)
			) // HashFilter      
		); // StringSource
	
	

	encoded.clear();
	StringSource(mac, true,
		new Base64Encoder(
			new StringSink(encoded),
                        false //don't insert newlines
		) // Base64Encoder
	); // StringSource

	return encoded;
}
ZObject init()
{
  Module* m = vm_allocModule();
  m->name = "hmac";
  Module_addSigNativeFun(m,"sign",&SIGN,"ss");
  return ZObjFromModule(m);
}
ZObject SIGN(ZObject* args,int32_t n)
{
  const char* plain = AS_STR(args[0])->val;
  const char* key = AS_STR(args[1])->val;
  try
  {
    string output = sign(key,plain);
    return ZObjFromStr(output.c_str());
  }
  catch(const CryptoPP::Exception& e)
  {
    return Z_Err(Error,e.what());
  }
}
