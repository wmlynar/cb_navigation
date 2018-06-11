#include "tue/profiling/profiler.h"

#include <iostream>

namespace tue
{

// ----------------------------------------------------------------------------------------------------

Profiler::Profiler() : head_(0), parent_(0)
{
}

// ----------------------------------------------------------------------------------------------------

Profiler::Profiler(const std::string& name) : name_(name), head_(0), parent_(0)
{
}

// ----------------------------------------------------------------------------------------------------

Profiler::Profiler(const std::string& name, Profiler* parent) : name_(name), head_(0), parent_(parent)
{
}

// ----------------------------------------------------------------------------------------------------

Profiler::~Profiler()
{
    for(std::map<std::string, Profiler*>::iterator it = children_.begin(); it != children_.end(); ++it)
    {
        delete it->second;
    }
}

// ----------------------------------------------------------------------------------------------------

void Profiler::startTimer(const std::string& name)
{
    if (!head_)
    {
        head_ = this;
    }

    Profiler* child;
    std::map<std::string, Profiler*>::iterator it_child = head_->children_.find(name);
    if (it_child != head_->children_.end())
    {
        child = it_child->second;
    }
    else
    {
        child = new Profiler(name, head_);
        head_->children_[name] = child;
    }

    head_ = child;

    child->timer_.start();
}

// ----------------------------------------------------------------------------------------------------

void Profiler::stopTimer()
{
    if (!head_)
    {
        std::cout << "[tue::Profiler] stopTimer() called, but no timer is active." << std::endl;
        return;
    }

    head_->timer_.stop();
    head_ = head_->parent_;
}

// ----------------------------------------------------------------------------------------------------

void Profiler::addToStream(std::ostream& out, const std::string& prefix) const
{
    if (!parent_)
    {
        out << prefix << "[" << name_ << "]" << std::endl;
    }
    else
    {
        out << prefix << name_ << ": " << timer_.getElapsedTimeInMilliSec() << " ms" << std::endl;
    }

    for(std::map<std::string, Profiler*>::const_iterator it = children_.begin(); it != children_.end(); ++it)
    {
        it->second->addToStream(out, prefix + "  ");
    }
}

// ----------------------------------------------------------------------------------------------------

std::ostream& operator<<(std::ostream& out, const Profiler& p)
{
    p.addToStream(out);
    return out;
}

}
