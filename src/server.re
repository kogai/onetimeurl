let hello = (event, _context, callback) =>
  callback(
    Js.null,
    {
      "statusCode": 200,
      "body":
        Js.Json.stringifyAny({
          "message": "Go Serverless v1.0! Your function executed successfully!",
          "input": event,
        }),
    },
  );
