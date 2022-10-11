#include "middleware/request-middleware.h"
#include "utils/utils.h"
#include "middleware/validation/request-validation-middleware.h"
#include <string.h>
#include "types/error-or-response-dto.h"

using namespace std;

RequestMiddleware::RequestMiddleware(Cb cb, IGps gps)
{
  this->cb = cb;
  this->requestController = RequestController(cb, gps);
};

ResponseModel RequestMiddleware::execute(string request)
{

  loggerInfo("RequestMiddleware.execute", "Process started", "Serial info. available, cbId: " + this->cb.getId());

  ErrorOrBool erroOrBool = requestValidationMiddleware.validate(request);
  if (erroOrBool.isError())
  {
    loggerError("RequestMiddleware.execute", "Process error", "error: " + erroOrBool.getError().description);
    cb.display.clearDisplay();
    cb.display.print(erroOrBool.getError().description, 0, 0);
    cb.display.print(erroOrBool.getError().errorCode, 0, 0);

    ResponseModel responseModel(erroOrBool.getError().errorCode);

    return responseModel;
  }

  RequestDto requestDto(request);

  ErrorOrResponseDto errorOrResponseDto = requestController.execute(requestDto);
  if (errorOrResponseDto.isError())
  {
    loggerError("RequestMiddleware.execute", "Process error", "error: " + errorOrResponseDto.getError().description);

    cb.display.clearDisplay();
    cb.display.print(erroOrBool.getError().description, 0, 0);
    cb.display.print(erroOrBool.getError().errorCode, 0, 0);

    ResponseModel responseModel(errorOrResponseDto.getError().errorCode);

    return responseModel;
  }

  ResponseModel responseModel(errorOrResponseDto.getResponseDto());

  loggerInfo("RequestMiddleware.execute", "Process finished");

  return responseModel;
}
