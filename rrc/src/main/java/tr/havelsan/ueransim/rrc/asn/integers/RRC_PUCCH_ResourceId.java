package tr.havelsan.ueransim.rrc.asn.integers;

import tr.havelsan.ueransim.asn.core.AsnInteger;

// VALUE(0..127)
public class RRC_PUCCH_ResourceId extends AsnInteger {
    public RRC_PUCCH_ResourceId() {
    }
    
    public RRC_PUCCH_ResourceId(long value) {
        super(value);
    }
}
