#include "assert.h"
#include "minijson_stream.h"

module(json_stream)
{
    suite("# write")
    {
        string_t buf = NULL;
        size_t len = 0;
        json_stream_t * stream;

        test("# stdout")
        {
            stream = json_stream_new(JSON_STREAM_FILE, (void**)stdout);

            stream->write(stream, "Hello World!\n");
            stream->write(stream, "%d %s %f\n", 100, "Hello World Again", 10.4);

            json_stream_destroy(stream);
        } end


        test("# buffer")
        {
            stream = json_stream_new(JSON_STREAM_BUFFER, (void**)&buf);

            len = stream->write(stream, "Hello World!\n");
            len += stream->write(stream, "%d %s %f\n", 100, "Hello World Again", 10.4);

            expect_string(buf) to be equal ("Hello World!\n100 Hello World Again 10.400000\n");

            json_stream_destroy(stream);
        } end
    } end
}

int main()
{
    register_module(json_stream);

    run_all();
}
