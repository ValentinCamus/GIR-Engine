#pragma once

namespace gir
{
    class ImGuiWidget
    {
    public:
        explicit ImGuiWidget(const char* name, bool isVisible = true)
            : m_name(name)
            , m_isVisible(isVisible)
        {

        }

        /// Default destructor.
        virtual ~ImGuiWidget() = default;

        /// Called every tick to draw the widget content.
        virtual void Draw() = 0;

        inline void Show() { m_isVisible = true; }
        inline void Hide() { m_isVisible = false; }
        inline bool IsVisible() const { return m_isVisible; }

        inline const char* GetName() const { return m_name; }
        inline void SetName(const char* name) { m_name = name; }

    protected:
        /// The widget name.
        const char* m_name;

        /// Is the widget visible ?
        bool m_isVisible;
    };
}