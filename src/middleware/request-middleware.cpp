#include "middleware/request-middleware.h"
#include "utils/utils.h"
#include "middleware/validation/request-validation-middleware.h"
#include <string.h>

using namespace std;

RequestMiddleware::RequestMiddleware(Cb *cb, IGps *gps, ILcd *lcd, Timer *timer, Preferences *preferences)
{
  this->lcd = lcd;
  this->cb = cb;
  this->requestController = RequestController(cb, gps, lcd, preferences);
  this->timer = timer;
};

ResponseModel RequestMiddleware::execute(string request)
{
  logger(request);
  loggerInfo("RequestMiddleware.execute", "Process started", "Serial info. available, cbId: " + this->cb->getId());

  pair<bool, ERROR_TYPE *> errorOrBool = requestValidationMiddleware.validate(request);
  if (errorOrBool.second != nullptr)
  {
    loggerError("RequestMiddleware.execute", "Process error", "error: " + errorOrBool.second->description);
    this->lcd->clear();
    this->lcd->print(errorOrBool.second->errorCode, 0, 0);
    this->lcd->print(errorOrBool.second->description, 0, 1);
    this->timer->setTimer(1500)->wait();

    ResponseModel responseModel(errorOrBool.second->errorCode);

    return responseModel;
  }

  RequestDto requestDto(request);

  pair<ResponseDto, ERROR_TYPE *> errorOrResponseDto = requestController.execute(requestDto);
  if (errorOrResponseDto.second != nullptr)
  {
    loggerError("RequestMiddleware.execute", "Process error", "error: " + errorOrResponseDto.second->description);

    this->lcd->clear();
    this->lcd->print(errorOrResponseDto.second->errorCode, 0, 0);
    this->lcd->print(errorOrResponseDto.second->description, 0, 1);
    this->timer->setTimer(1500)->wait();

    ResponseModel responseModel(&errorOrResponseDto.first, errorOrResponseDto.second->errorCode);

    return responseModel;
  }

  ResponseModel responseModel(&errorOrResponseDto.first);

  return responseModel;
}
