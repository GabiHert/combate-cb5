#include "middleware/request-middleware.h"
#include "utils/utils.h"
#include "middleware/validation/request-validation-middleware.h"
#include <string.h>
#include "types/error-or-response-dto.h"

using namespace std;

RequestMiddleware::RequestMiddleware(Cb *cb, IGps *gps, ILcd *lcd, Timer *timer)
{
  this->lcd = lcd;
  this->cb = cb;
  this->requestController = RequestController(cb, gps, lcd);
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

  ErrorOrResponseDto errorOrResponseDto = requestController.execute(requestDto);
  if (errorOrResponseDto.isError())
  {
    loggerError("RequestMiddleware.execute", "Process error", "error: " + errorOrResponseDto.getError().description);

    this->lcd->clear();
    this->lcd->print(errorOrResponseDto.getError().errorCode, 0, 0);
    this->lcd->print(errorOrResponseDto.getError().description, 0, 1);
    this->timer->setTimer(1500)->wait();

    ResponseModel responseModel(errorOrResponseDto.getResponseDto(), errorOrResponseDto.getError().errorCode);

    return responseModel;
  }

  ResponseModel responseModel(errorOrResponseDto.getResponseDto());

  loggerInfo("RequestMiddleware.execute", "Process finished");

  return responseModel;
}
