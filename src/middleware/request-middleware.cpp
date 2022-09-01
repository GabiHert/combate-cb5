#include "middleware/request-middleware.h"
#include "utils/utils.h"
#include "middleware/validation/request-validation-middleware.h"

RequestMiddleware::RequestMiddleware(Cb cb)
{
  this->cb = cb;
  this->requestController = RequestController(cb);
};

ResponseModel RequestMiddleware::execute(String request)
{

  loggerInfo("RequestMiddleware.execute", "Process started", "Serial info. available");

  bool isRequestValid = requestValidationMiddleware.validate(request);
  RequestDto requestDto(request);

  if (isRequestValid)
  {
    ResponseDto responseDto = requestController.execute(requestDto);
    ResponseModel responseModel(responseDto);
    loggerInfo("RequestMiddleware.execute", "Process finished");
    return responseModel;
  }
  else
  {

    ResponseModel responseModel("001");
    loggerError("RequestMiddleware.execute", "Process error");

    return responseModel;
  }
}
