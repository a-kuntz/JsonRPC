#include <jsonrpc/net/ServerTransport.h>
#include <jsonrpc/rpc/Dispatcher.h
#include "x_ray_tube.h"
#include <string>

using namespace jsonrpc;

struct XRayTube::setTubeVoltage
{
  rpc ::Json call(const rpc::Json& data) override
  {
    //TODO: error handling (check if Voltage is in range)
    if (data.is_array())
    {
      std::array<double, 1> par = data;
      voltage                   = par[0];
    }
    else if (data.is_object())
    {
      voltage = data.at("voltage");
    }
    return "Tube Voltage has been set to" + voltage;
  }
}

struct XRayTube::setTubeCurrent
{
  rpc ::Json call(const rpc::Json& data) override
  {
    //TODO: error handling (check if Current is in range)
    if (data.is_array())
    {
      std::array<double, 1> par = data;
      current                   = par[0];
    }
    else if (data.is_object())
    {
      current = data.at("current");
    }
    return "Tube Current has been set to" + current;
  }
}

struct XRayTube::getStatus
{
  rpc ::Json call(const rpc::Json& data) override
  {
    if (voltage == NULL)
    {
      return "Tube Voltage is not set."
    }
    else if (current == NULL)
    {
      return "Tube Current is not set."
    }
    else if (voltage == NULL && current == NULL)
    {
      return "Tube Current and Tube Voltage are not set."
    }
    else
    {
      return "Current settings are: Tube Voltage = " + voltage + " Tube Current = " + current;
    }
  }
}

struct XRayTube::takePicture
{
  rpc ::Json call(const rpc::Json& data) override
  {
    return "Picture taken."
  }
}
