#include "Material.hpp"

namespace uGE
{

    Material::Material()
    {
        //ctor
    }

    Material::~Material()
    {
        //dtor
    }

    // === Setters ===

    void Material::setOverhang( bool value, float alpha )
    {
        overhang = value;
        overhangAlpha = alpha;
    }

    void Material::setAlpha( float value )
    {
        alpha = value;
    }

    void Material::setColor( glm::vec3 rgb )
    {
        color = rgb;
    }

    void Material::setColor( glm::vec4 rgba )
    {
        color = glm::vec3( rgba[0], rgba[1], rgba[2] );
        alpha = rgba[3];
    }

    void Material::setBlendMode( BlendMode mode )
    {
        blend = mode;
    }

    // === Getters ===

    bool Material::isOverhang()
    {
        return overhang;
    }

    float Material::getOverhangAlpha()
    {
        return overhangAlpha;
    }

    float Material::getAlpha()
    {
        return alpha;
    }

    glm::vec3 Material::getColor()
    {
        return color;
    }

    Material::BlendMode Material::getBlendMode()
    {
        return blend;
    }


    void Material::applyBlendMode()
    {
        switch( blend ) {
        case BlendMode::NORMAL:
            glBlendFunc( GL_ONE, GL_ZERO );
            break;
        case BlendMode::ALPHA:
            glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
            break;
        case BlendMode::ADD:
            glBlendFunc( GL_ONE, GL_ONE );
            break;
        case BlendMode::SUB:
            glBlendFunc( GL_ZERO, GL_SRC_ALPHA );
            break;
        }
    }
}
