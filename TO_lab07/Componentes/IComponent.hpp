#ifndef ICOMPONENT_HPP
#define ICOMPONENT_HPP

class IComponent {
public:
    virtual ~IComponent() {}
    virtual void apply() = 0;
};

#endif // ICOMPONENT_HPP
