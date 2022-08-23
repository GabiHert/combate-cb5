#include "middleware/request-middleware.h"
#include "utils/utils.h"
#include "middleware/validation/request-validation-middleware.h"

RequestMiddleware::RequestMiddleware(Cb cb)
{
  this->cb = cb;
  this->requestController = RequestController(cb);
};

String RequestMiddleware::execute(String request)
{

  loggerInfo("main", "Process started", "Serial info. available");

  bool isRequestValid = requestValidationMiddleware.validate(request);
  RequestDto requestDto(request);

  String response;

  if (isRequestValid)
  {
    response = requestController.execute(requestDto);
  }

  loggerInfo("main", "Process finished");
  return response;
}
