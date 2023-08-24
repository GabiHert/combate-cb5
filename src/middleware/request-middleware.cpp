#include "middleware/request-middleware.h"
#include "utils/utils.h"
#include "middleware/validation/request-validation-middleware.h"
#include <string.h>

using namespace std;

RequestMiddleware::RequestMiddleware(Cb *cb, IGps *gps, ILcd *lcd, Timer *timer, Preferences *preferences)
{
  this->lcd = lcd;
  this->cb = cb;
  this->requestController = RequestController(cb, gps, lcd, preferences, timer);
  this->timer = timer;
};

ResponseModel RequestMiddleware::execute(string request)
{
  //logger(request);
  //loggerInfo("RequestMiddleware.execute", "Process started", "Serial info. available, cbId: " + this->cb->id);

  pair<bool, ERROR_TYPE *> errorOrBool = requestValidationMiddleware.validate(request);
  if (errorOrBool.second != nullptr)
  {
    if (requestValidationMiddleware.validateSimpleV4(request))
    {
      // Parse to simple V5 request
      char cs = 217;
      request = "INF5N000NNx";
      request += cs;
      request += "\r\n";
    }
    else
    {
      //loggerError("RequestMiddleware.execute", "Process error", "error: " + errorOrBool.second->description);
      this->lcd->print(errorOrBool.second);
      this->timer->setTimer(1500)->wait();

      ResponseModel responseModel(errorOrBool.second->errorCode);

      return responseModel;
    }
  }

  RequestDto requestDto(request);

  pair<ResponseDto, ERROR_TYPE *> errorOrResponseDto = requestController.execute(requestDto);
  if (errorOrResponseDto.second != nullptr)
  {

    //loggerError("RequestMiddleware.execute", "Process error", "error: " + errorOrResponseDto.second->description);

    this->lcd->print(errorOrResponseDto.second);
    this->timer->setTimer(1500)->wait();

    ResponseModel responseModel(&errorOrResponseDto.first, errorOrResponseDto.second->errorCode);

    return responseModel;
  }

  ResponseModel responseModel(&errorOrResponseDto.first);

  return responseModel;
}
