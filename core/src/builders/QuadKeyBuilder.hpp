#ifndef BUILDERS_QUADKEYBUILDER_HPP_DEFINED
#define BUILDERS_QUADKEYBUILDER_HPP_DEFINED

#include "CancellationToken.hpp"
#include "QuadKey.hpp"
#include "builders/BuilderContext.hpp"
#include "builders/ElementBuilder.hpp"
#include "entities/Element.hpp"
#include "heightmap/ElevationProvider.hpp"
#include "index/GeoStore.hpp"
#include "mapcss/StyleProvider.hpp"
#include "math/Mesh.hpp"

#include <functional>
#include <string>

namespace utymap { namespace builders {

/// Responsible for building single quadkey.
class QuadKeyBuilder final
{
public:
    typedef std::function<void(const utymap::math::Mesh&)> MeshCallback;
    typedef std::function<void(const utymap::entities::Element&)> ElementCallback;
    /// Factory of element builders
    typedef std::function<std::unique_ptr<utymap::builders::ElementBuilder>(const utymap::builders::BuilderContext&)> ElementBuilderFactory;

    QuadKeyBuilder(utymap::index::GeoStore& geoStore,
                   utymap::index::StringTable& stringTable);

    ~QuadKeyBuilder();

    /// Registers factory method for element builder.
    void registerElementBuilder(const std::string& name, ElementBuilderFactory factory);

    /// Builds tile for given quadkey.
    void build(const utymap::QuadKey& quadKey,
               const utymap::mapcss::StyleProvider& styleProvider,
               const utymap::heightmap::ElevationProvider& eleProvider,
               MeshCallback meshFunc,
               ElementCallback elementFunc,
               const utymap::CancellationToken& cancelToken);

private:
    class QuadKeyBuilderImpl;
    std::unique_ptr<QuadKeyBuilderImpl> pimpl_;
};

}}
#endif // BUILDERS_QUADKEYBUILDER_HPP_DEFINED
