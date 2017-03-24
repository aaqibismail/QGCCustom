/****************************************************************************
 *
 *   (c) 2009-2016 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

#include "YuneecAutoPilotPlugin.h"

YuneecAutoPilotPlugin::YuneecAutoPilotPlugin(Vehicle* vehicle, QObject* parent)
    : PX4AutoPilotPlugin(vehicle, parent)
{

}

const QVariantList& YuneecAutoPilotPlugin::vehicleComponents(void)
{
    if (_components.count() == 0 && !_incorrectParameterVersion) {
        if (_vehicle->parameterManager()->parametersReady()) {
            _sensorsComponent = new SensorsComponent(_vehicle, this);
            _sensorsComponent->setupTriggerSignals();
            _components.append(QVariant::fromValue((VehicleComponent*)_sensorsComponent));

            _safetyComponent = new SafetyComponent(_vehicle, this);
            _safetyComponent->setupTriggerSignals();
            _components.append(QVariant::fromValue((VehicleComponent*)_safetyComponent));
        } else {
            qWarning() << "Call to vehicleComponents prior to parametersReady";
        }
    }

    return _components;
}