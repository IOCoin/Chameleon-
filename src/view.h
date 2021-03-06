// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#ifndef IOCOIN_VIEW_H
#define IOCOIN_VIEW_H

#include "crypter.h"
#include "sync.h"
#include <boost/signals2/signal.hpp>
#include "keystore.h"
class CScript;
class cba;

typedef std::set<CKeyID> ViewSet;
class CViewKeyStore : public CKeyStore
{
protected:
    ViewSet mapKeys;
    ScriptMap mapScripts;

public:
    bool ak(const CKeyID& );
    bool HaveKey(const CKeyID &address) const
    {
        bool result;
        {
            LOCK(cs_KeyStore);
            result = (mapKeys.count(address) > 0);
        }
        return result;
    }
    void GetKeys(std::set<CKeyID> &setAddress) const
    {
        setAddress.clear();
        {
            LOCK(cs_KeyStore);
            ViewSet::const_iterator mi = mapKeys.begin();
            while (mi != mapKeys.end())
            {
                setAddress.insert((*mi));
                mi++;
            }
        }
    }
    virtual bool AddCScript(const CScript& redeemScript);
    virtual bool HaveCScript(const CScriptID &hash) const;
    virtual bool GetCScript(const CScriptID &hash, CScript& redeemScriptOut) const;
};
#endif
