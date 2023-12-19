#include "middleware/request-middleware.h"
#include "utils/utils.h"
#include "middleware/validation/request-validation-middleware.h"
#include <string.h>

using namespace std;

RequestMiddleware::RequestMiddleware(Cb *cb, IGps *gps, ILcd *lcd, Timer *timer, Preferences *preferences)
{
  this->_lcd = lcd;
  this->_cb = cb;
  this->_requestController = RequestController(cb, gps, lcd, preferences, timer);
  this->_timer = timer;
};

ResponseModel RequestMiddleware::execute(string request)
{
  // // logger(request);
  // // loggerInfo("RequestMiddleware.execute", "Process started", "Serial info. available, cbId: " + this->_cb->id);

  pair<bool, ERROR_TYPE *> errorOrBool = this->_requestValidationMiddleware.validate(request);
  if (errorOrBool.second != nullptr)
  {
    if (this->_requestValidationMiddleware.validateSimpleV4(request))
    {
      // Parse to simple V5 request
      char cs = 217;
      request = "INF5N000NNx";
      request += cs;
      request += "\r\n";
    }
    else
    {
      // // loggerError("RequestMiddleware.execute", "Process error", "error: " + errorOrBool.second->description);
      this->_lcd->print(errorOrBool.second);
      this->_timer->setTimer(1500);
      this->_timer->wait();

      ResponseModel responseModel(errorOrBool.second->errorCode);

      return responseModel;
    }
  }

  RequestDto requestDto(request);

  pair<ResponseDto, ERROR_TYPE *> errorOrResponseDto = this->_requestController.execute(requestDto);
  if (errorOrResponseDto.second != nullptr)
  {

    // // loggerError("RequestMiddleware.execute", "Process error", "error: " + errorOrResponseDto.second->description);

    this->_lcd->print(errorOrResponseDto.second);
    this->_timer->setTimer(1500);
    this->_timer->wait();

    ResponseModel responseModel(&errorOrResponseDto.first, errorOrResponseDto.second->errorCode);

    return responseModel;
  }

  ResponseModel responseModel(&errorOrResponseDto.first);

  return responseModel;
};

void RequestMiddleware::systematic()
{
  // // loggerInfo("RequestMiddleware.systematic", "Process started");

  ERROR_TYPE *error = this->_requestController.systematic();
  if (error != nullptr)
  {
    // // loggerError("RequestMiddleware.systematic", "Process error", "error: " + error->description);

    this->_lcd->print(error);
    this->_timer->setTimer(1500);
    this->_timer->wait();
  }
  // // loggerInfo("RequestMiddleware.systematic", "Process finished");
}
