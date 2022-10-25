#include <jsonrpc/net/ServerTransport.h>
#include <jsonrpc/rpc/Dispatcher.h>

#include "settings.h"
using namespace jsonrpc;

class settings
{
private:
	bool flagDate     = false;
	bool flagContrast = false;
	double contrast;
	double brightness;
	dateTime date;
	Time time;
public:
	struct Date : public rpc::IMethod
	{
		rpc ::Json call(const rpc::Json& data) override
		{
			//date = data;
			flagDate = true;
			return "setDate has been called";
		}
	};
	struct Time : public rpc::IMethod
	{
		rpc ::Json call(const rpc::Json& data) override
		{
			if (flagDate != true)
			{
				return "setDate has to been called before calling setTime";
			}
			else
			{
				//time = data;
				return "setTime has been called";
			}
		}
	};

	struct Contrast : public rpc::IMethod
	{
		rpc ::Json call(const rpc::Json& data) override
		{
			flagContrast = true;
			//contrast = data;
			return "setContrast has been called";
		}
	};
	struct Brightness : public rpc::IMethod
	{
		rpc ::Json call(const rpc::Json& data) override
		{
			if (flagContrast != true)
			{
				return "setContrast has to been called before calling setBrightness";
			}
			else
			{
				//brightness = data;
				return "setBrightness has been called";
			}
		}
	};
}