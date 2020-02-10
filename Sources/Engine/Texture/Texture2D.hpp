#pragma once

#include <glad/glad.h>
#include <Core/Core.hpp>
#include <Engine/Component/OpenGLComponent.hpp>

namespace gir
{
    class Texture2D : public OpenGLComponent
    {
    public:
        /// Constructor.
        /// @name: specifies the name of the component.
        /// @format: specifies the number of color components in the texture.
        /// @type: specifies the data type of the pixel data.
        explicit Texture2D(const std::string& name, int format, int type);

        /// Constructor.
        /// @name: specifies the name of the component.
        /// @format: specifies the number of color components in the texture.
        /// @internalFormat: ...
        /// @type: specifies the data type of the pixel data.
        explicit Texture2D(const std::string& name, int format, int internalFormat, int type);

        /// Destructor.
        ~Texture2D() override;

        /// Allocate the texture with the given dimension.
        /// @pixels: specifies a pointer to the image data in memory.
        void Allocate(unsigned width, unsigned height, const unsigned char* pixels = nullptr);

        void Bind() override;

        void Unbind() override;

        /// Bind the image and selects which texture unit subsequent texture state calls will affect.
        /// The number of texture units an implementation supports is implementation dependent, but must be at least 80.
        void Bind(int slot);

        /// The index of the texture unit.
        inline int GetSlot() const { return m_slot; }

        inline unsigned GetWidth() const { return m_width; }

        inline unsigned GetHeight() const { return m_height; }

        /// @return: the number of color components in the texture.
        inline int GetFormat() const { return m_format; }

        /// @return: the data type of the pixel data.
        inline int GetType() const { return m_type; }

        /// @setter: Define an int texture parameter.
        void SetParameter(int name, int value);

        /// @setter: Define a float texture parameter.
        void SetParameter(int name, float value);

    private:
        /// The index of the texture unit.
        /// @note: -1 is the null/invalid texture index.
        int m_slot = -1;

        unsigned m_width = 0;

        unsigned m_height = 0;

        /// The number of color components in the texture.
        int m_format = GL_RGBA;

        int m_internalFormat = GL_RGBA;

        /// The data type of the pixel data.
        int m_type = GL_UNSIGNED_INT;
    };
} // namespace gir
