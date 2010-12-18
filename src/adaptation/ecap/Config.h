/*
 * $Id$
 * DEBUG: section 93    eCAP Interface
 */

#ifndef SQUID_ECAP_CONFIG_H
#define SQUID_ECAP_CONFIG_H

#include "adaptation/Config.h"
#include "adaptation/ServiceConfig.h"
#include <list>
#include <utility>

namespace Adaptation
{
namespace Ecap
{

class ServiceConfig: public Adaptation::ServiceConfig {
public:
    // Adaptation::ServiceConfig API
    virtual bool grokExtension(const char *name, const char *value);

public:
    typedef std::pair<std::string, std::string> Extension; // name=value in cfg
    typedef std::list<Extension> Extensions;
    Extensions extensions;
};


class Config: public Adaptation::Config
{

public:
    Config();
    ~Config();

    virtual void finalize();

protected:
    virtual Adaptation::ServiceConfig *newServiceConfig() const;

private:
    Config(const Config &); // not implemented
    Config &operator =(const Config &); // not implemented

    virtual Adaptation::ServicePointer createService(ServiceConfigPointer cfg);
};

extern Config TheConfig;

} // namespace Ecap
} // namespace Adaptation

#endif /* SQUID_ECAP_CONFIG_H */
