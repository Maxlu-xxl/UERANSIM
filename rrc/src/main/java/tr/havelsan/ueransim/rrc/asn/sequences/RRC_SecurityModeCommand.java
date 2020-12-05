package tr.havelsan.ueransim.rrc.asn.sequences;

import tr.havelsan.ueransim.asn.core.AsnChoice;
import tr.havelsan.ueransim.asn.core.AsnSequence;
import tr.havelsan.ueransim.rrc.asn.integers.RRC_RRC_TransactionIdentifier;

public class RRC_SecurityModeCommand extends AsnSequence {
    public RRC_RRC_TransactionIdentifier rrc_TransactionIdentifier; // mandatory
    public RRC_criticalExtensions_11 criticalExtensions; // mandatory

    public static class RRC_criticalExtensions_11 extends AsnChoice {
        public RRC_SecurityModeCommand_IEs securityModeCommand;
        public RRC_criticalExtensionsFuture_14 criticalExtensionsFuture;
    
        public static class RRC_criticalExtensionsFuture_14 extends AsnSequence {
        }
    }
}
