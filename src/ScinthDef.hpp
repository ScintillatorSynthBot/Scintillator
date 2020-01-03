#ifndef SRC_SCINTHDEF_HPP_
#define SRC_SCINTHDEF_HPP_

#include "core/Types.hpp"

#include <memory>

namespace scin {

class AbstractScinthDef;
class Scinth;

namespace vk {
class Canvas;
class CommandPool;
class Device;
class HostBuffer;
class Pipeline;
class Shader;
class ShaderCompiler;
class UniformLayout;
}

/*! A ScinthDef encapsulates all of the graphics state that can be reused across individual instances of Scinths.
 */
class ScinthDef {
public:
    ScinthDef(std::shared_ptr<vk::Device> device, std::shared_ptr<vk::Canvas> canvas,
              std::shared_ptr<vk::CommandPool> commandPool, std::shared_ptr<const AbstractScinthDef> abstractScinthDef);
    ~ScinthDef();

    /*! Given the AbstractScinthDef, build the Vulkan objects that can be re-used across all running Scinth instances
     * of this ScinthDef.
     *
     * \param A pointer to the ShaderCompiler.
     * \return true on success, false on error.
     */
    bool build(vk::ShaderCompiler* compiler);

    // TODO: whatever happend to create/destroy paradigm?

    /*! Create a running instance Scinth of this ScinthDef.
     */
    std::unique_ptr<Scinth> play(const std::string& scinthName, const TimePoint& startTime);

private:
    bool buildVertexData();

    std::shared_ptr<vk::Device> m_device;
    std::shared_ptr<vk::Canvas> m_canvas;
    std::shared_ptr<vk::CommandPool> m_commandPool;
    std::shared_ptr<const AbstractScinthDef> m_abstractScinthDef;
    std::unique_ptr<vk::HostBuffer> m_vertexBuffer;
    std::unique_ptr<vk::HostBuffer> m_indexBuffer;
    std::unique_ptr<vk::Shader> m_vertexShader;
    std::unique_ptr<vk::Shader> m_fragmentShader;
    std::unique_ptr<vk::UniformLayout> m_uniformLayout;
    std::unique_ptr<vk::Pipeline> m_pipeline;
};

} // namespace scin

#endif // SRC_SCINTHDEF_HPP_