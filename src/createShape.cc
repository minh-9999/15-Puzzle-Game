#include "createShape.hh"
#include <numbers>
#include <cmath>

void centerText(sf::Text &text, float x, float y, float width, float height)
{
    sf::FloatRect bounds = text.getLocalBounds();
    // text.setOrigin({bounds.size.x / 2.0f, bounds.size.y / 2.0f});
    sf::Vector2f origin = bounds.position + bounds.size / 2.f;
    text.setOrigin(origin);
    text.setPosition({x + width / 2.f, y + height / 2.f});
}

sf::ConvexShape createRoundedRect(float width, float height, float radius, int pointCount)
{
    sf::ConvexShape shape;
    int totalPoints = (pointCount + 1) * 4; // 4 góc
    shape.setPointCount(totalPoints);

    float angle = 90.f / pointCount;
    int currentPoint = 0;

    // Góc trên trái
    for (int i = 0; i <= pointCount; ++i)
    {
        float rad = (180.f + i * angle) * std::numbers::pi_v<float> / 180.f;
        shape.setPoint(currentPoint++, {radius + radius * std::cos(rad),
                                        radius + radius * std::sin(rad)});
    }

    // Góc trên phải
    for (int i = 0; i <= pointCount; ++i)
    {
        float rad = (270.f + i * angle) * std::numbers::pi_v<float> / 180.f;
        shape.setPoint(currentPoint++, {width - radius + radius * std::cos(rad),
                                        radius + radius * std::sin(rad)});
    }

    // Góc dưới phải
    for (int i = 0; i <= pointCount; ++i)
    {
        float rad = (0.f + i * angle) * std::numbers::pi_v<float> / 180.f;
        shape.setPoint(currentPoint++, {width - radius + radius * std::cos(rad),
                                        height - radius + radius * std::sin(rad)});
    }

    // Góc dưới trái
    for (int i = 0; i <= pointCount; ++i)
    {
        float rad = (90.f + i * angle) * std::numbers::pi_v<float> / 180.f;
        shape.setPoint(currentPoint++, {radius + radius * std::cos(rad),
                                        height - radius + radius * std::sin(rad)});
    }

    return shape;
}