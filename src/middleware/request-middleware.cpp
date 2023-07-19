#include "middleware/request-middleware.h"
#include "utils/utils.h"
#include "middleware/validation/request-validation-middleware.h"
#include <string.h>
#include "types/error-or-response-dto.h"

using namespace std;

RequestMiddleware::RequestMiddleware(Preferences *preferences, Cb *cb, IGps *gps, ILcd *lcd, Timer *timer)
{
  this->lcd = lcd;
  this->cb = cb;
  this->_requestController = RequestController(preferences, cb, gps, lcd);
  this->timer = timer;
};

ResponseModel RequestMiddleware::execute(string request)
{
  loggerInfo("RequestMiddleware.execute", "Process started", "Serial info. available, cbId: " + this->cb->getId());

  ErrorOrBool erroOrBool = requestValidationMiddleware.validate(request);
  if (erroOrBool.isError())
  {
    loggerError("RequestMiddleware.execute", "Process error", "error: " + erroOrBool.getError().description);
    this->lcd->clear();
    this->lcd->print(erroOrBool.getError().errorCode, 0, 0);
    this->lcd->print(erroOrBool.getError().description, 0, 1);
    this->timer->setTimer(1500)->wait();

    ResponseModel responseModel(erroOrBool.getError().errorCode);

    return responseModel;
  }

  request = this->parseV4ToV5(request);

  RequestDto requestDto(request);

  ErrorOrResponseDto errorOrResponseDto = _requestController.execute(requestDto);
  if (errorOrResponseDto.isError())
  {
    loggerError("RequestMiddleware.execute", "Process error", "error: " + errorOrResponseDto.getError().description);

    this->lcd->clear();
    this->lcd->print(errorOrResponseDto.getError().errorCode, 0, 0);
    this->lcd->print(errorOrResponseDto.getError().description, 0, 1);
    this->timer->setTimer(1500)->wait();

    ResponseModel responseModel(errorOrResponseDto.getError().errorCode);

    return responseModel;
  }

  ResponseModel responseModel(errorOrResponseDto.getResponseDto());

  loggerInfo("RequestMiddleware.execute", "Process finished");

  return responseModel;
}

string RequestMiddleware::parseV4ToV5(string request)
{
  if (request[3] != '5')
  {
    request[3] = '5';
    request[4] = 'S';
  }

  return request;
}
