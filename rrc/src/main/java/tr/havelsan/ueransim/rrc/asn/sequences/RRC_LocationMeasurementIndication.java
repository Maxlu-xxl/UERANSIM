package tr.havelsan.ueransim.rrc.asn.sequences;

import tr.havelsan.ueransim.asn.core.AsnChoice;
import tr.havelsan.ueransim.asn.core.AsnSequence;

public class RRC_LocationMeasurementIndication extends AsnSequence {
    public RRC_criticalExtensions_15 criticalExtensions; // mandatory

    public static class RRC_criticalExtensions_15 extends AsnChoice {
        public RRC_LocationMeasurementIndication_IEs locationMeasurementIndication;
        public RRC_criticalExtensionsFuture_8 criticalExtensionsFuture;
    
        public static class RRC_criticalExtensionsFuture_8 extends AsnSequence {
        }
    }
}
