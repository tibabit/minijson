#include "../src/minijson_stream.h"

int main()
{
    string_t buf = NULL;
    size_t len = 0;
    json_stream_t * stream = json_stream_new(JSON_STREAM_FILE, (void**)stdout);

    stream->write(stream, "Hello World!\n");
    stream->write(stream, "%d %s %f\n", 100, "Hello World Again", 10.4);

    json_stream_destroy(stream);


    stream = json_stream_new(JSON_STREAM_BUFFER, (void**)&buf);

    len = stream->write(stream, "Hello World!\n");
    len += stream->write(stream, "%d %s %f\n", 100, "Hello World Again", 10.4);
    printf("%s", buf);

    json_stream_destroy(stream);

    return 0;
}
