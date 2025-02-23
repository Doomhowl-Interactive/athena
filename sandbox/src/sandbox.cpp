
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
    auto path = std::filesystem::path("./assets.doom");

    try
    {
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
        std::cerr << "Failed to save asset bundle: " << ex.what() << '\n';
    }

    Texture wolfTexture;

    InitWindow(800, 600, "raylib athena asset serialization");

    try {
        auto streamReader = athena::fileStreamReader(path);

        // TODO: Leaks memory
        auto pkgHeader = streamReader.readObject<DoomPackageHeader>();

        std::cout << "Magic: " << pkgHeader.magic << '\n';
        std::cout << "Version: " << pkgHeader.version << '\n';
        std::cout << "Asset count: " << pkgHeader.assetCount << '\n';
        
        for (int i = 0; i < pkgHeader.assetCount; i++)
        {
            streamReader.nextStreamSection();

            auto asset = streamReader.readObject<DoomAssetHeader>();
            auto rawData = reinterpret_cast<const unsigned char*>(streamReader.readData(asset.size));

            const char* ext = GetFileExtension(asset.fileName);
            wolfTexture = LoadTextureFromImage(LoadImageFromMemory(ext, rawData, asset.size));
        }
    }
    catch (const std::exception& ex)
    {
        std::cerr << "Failed to load asset bundle: " << ex.what() << '\n';
    }

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawTexture(wolfTexture, 0, 0, WHITE);

        DrawText("it did the thing!", 190, 200, 20, LIGHTGRAY);

        EndDrawing();
    }
}
