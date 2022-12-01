#include "middleware/request-middleware.h"
#include "utils/utils.h"
#include "middleware/validation/request-validation-middleware.h"
#include <string.h>
#include "types/error-or-response-dto.h"

using namespace std;

RequestMiddleware::RequestMiddleware(Cb *cb, IGps *gps, IDisplay *display)
{
  this->display = display;
  this->cb = cb;
  this->requestController = RequestController(cb, gps, display);
};

ResponseModel RequestMiddleware::execute(string request)
{
  Timer timer;

  loggerInfo("RequestMiddleware.execute", "Process started", "Serial info. available, cbId: " + this->cb->getId());

  ErrorOrBool erroOrBool = requestValidationMiddleware.validate(request);
  if (erroOrBool.isError())
  {
    loggerError("RequestMiddleware.execute", "Process error", "error: " + erroOrBool.getError().description);
    this->display->clear();
    this->display->print(erroOrBool.getError().errorCode, 0, 0);
    this->display->print(erroOrBool.getError().description, 0, 1);
    timer.setTimer(1000);
    timer.wait();

    ResponseModel responseModel(erroOrBool.getError().errorCode);

    return responseModel;
  }

  RequestDto requestDto(request);

  ErrorOrResponseDto errorOrResponseDto = requestController.execute(requestDto);
  if (errorOrResponseDto.isError())
  {
    loggerError("RequestMiddleware.execute", "Process error", "error: " + errorOrResponseDto.getError().description);

    this->display->clear();
    this->display->print(errorOrResponseDto.getError().errorCode, 0, 0);
    this->display->print(errorOrResponseDto.getError().description, 0, 1);
    timer.setTimer(1000);
    timer.wait();

    ResponseModel responseModel(errorOrResponseDto.getError().errorCode);

    return responseModel;
  }

  ResponseModel responseModel(errorOrResponseDto.getResponseDto());

  loggerInfo("RequestMiddleware.execute", "Process finished");

  return responseModel;
}
