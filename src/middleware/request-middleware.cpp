#include "middleware/request-middleware.h"
#include "utils/utils.h"
#include "middleware/validation/request-validation-middleware.h"
#include "exceptions/error.h"
#include <string.h>
using namespace std;

RequestMiddleware::RequestMiddleware(Cb cb)
{
  this->cb = cb;
  this->requestController = RequestController(cb);
};

ResponseModel RequestMiddleware::execute(string request)
{
  try
  {
    loggerInfo("RequestMiddleware.execute", "Process started", "Serial info. available, cbId: " + this->cb.getId());

    bool isRequestValid = requestValidationMiddleware.validate(request);
    RequestDto requestDto(request);
    ResponseDto responseDto = requestController.execute(requestDto);
    ResponseModel responseModel(responseDto);
    loggerInfo("RequestMiddleware.execute", "Process finished");
    return responseModel;
  }
  catch (Error err)
  {

    ResponseModel responseModel(err.errorType().errorCode);
    loggerError("RequestMiddleware.execute", "Process error", "error: " + err.message());

    return responseModel;
  }
}
