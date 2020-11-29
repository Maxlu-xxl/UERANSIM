/*
 * Copyright (c) 2020 ALİ GÜNGÖR (aligng1620@gmail.com)
 * This software and all associated files are licensed under GPL-3.0.
 */

package tr.havelsan.ueransim.app.common.dynamics;

import tr.havelsan.ueransim.app.common.PduSessionResource;

import java.util.HashMap;
import java.util.Map;
import java.util.UUID;

public class PduSessionTree {

    private final Map<Long, PduSessionResource> mapByUpTeid;
    private final Map<UUID, Map<Integer, PduSessionResource>> mapByUeId;

    public PduSessionTree() {
        this.mapByUpTeid = new HashMap<>();
        this.mapByUeId = new HashMap<>();
    }

    public void insert(PduSessionResource session) {
        mapByUpTeid.put(session.upLayer.gTPTunnel.gTP_TEID.value.get4(0).longValue(), session);

        var mapBySessionId = mapByUeId.computeIfAbsent(session.ueId, k -> new HashMap<>());
        mapBySessionId.put(session.pduSessionId, session);
    }

    public PduSessionResource findByUpTeid(long upTeid) {
        return mapByUpTeid.get(upTeid);
    }

    public PduSessionResource findBySessionId(UUID ue, int psi) {
        var mapBySessionId = mapByUeId.get(ue);
        if (mapBySessionId != null) {
            return mapBySessionId.get(psi);
        }
        return null;
    }

    public void delete(PduSessionResource session) {
        mapByUpTeid.remove(session.upLayer.gTPTunnel.gTP_TEID.value.get4(0).longValue());

        var mapBySessionId = mapByUeId.get(session.ueId);
        if (mapBySessionId != null) {
            mapBySessionId.remove(session.pduSessionId);
        }
    }
}
