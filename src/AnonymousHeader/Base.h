#pragma once
#include <QRect>
#include <QSize>
#include <chrono>
#include <QApplication>
#include <QDesktopWidget>

namespace lon {
namespace {
inline auto operator*(const QRect& lhs, const double& rhs) -> QRect {
    return QRect{lhs.left(), lhs.top(),
                 static_cast<int>(lhs.width() * rhs),
                 static_cast<int>(lhs.height() * rhs)};
}

auto getDesktopGeometry() -> QRect {
    return QApplication::desktop()->screenGeometry();
}

auto operator+(const QSize& lhs, const int& rhs) -> QSize {
    return {lhs.width() + rhs, lhs.height() + rhs};
}
}
}
