
#include <athena.h>
#include <iostream>
#include <raylib.h>
#include <vector>

struct DoomPackageHeader
{
    const char magic[13] = "DOOM";
    const uint32_t version = 1;
    const uint32_t assetCount;

    DoomPackageHeader() = default;

    DoomPackageHeader(int count) : assetCount(count)
    {
    }
};

struct DoomAssetHeader
{
    char fileName[128];
    uint64_t size;
};

int main()
{
    std::filesystem::current_path(std::filesystem::path(__FILE__).parent_path().parent_path());

    try
    {
        auto path = std::filesystem::path("./assets.doom");
        auto streamWriter = athena::fileStreamWriter(path);
        DoomPackageHeader pkgHeader{1};
        streamWriter.writeObject(pkgHeader);
        streamWriter.nextStreamSection();

        {
            int fileSize;
            unsigned char *data = LoadFileData("ComfyUI_00372_.png", &fileSize);

            auto header = DoomAssetHeader{"ComfyUI_00372_.png", static_cast<uint64_t>(fileSize)};
            streamWriter.writeObject(header);
            streamWriter.writeData((const char *)data, fileSize);
        }

        streamWriter.flush();
    }
    catch (const std::exception& ex)
    {
        std::cerr << ex.what() << std::endl;
    }

    InitWindow(800, 600, "raylib athena asset serialization");
    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

        EndDrawing();
    }
}
