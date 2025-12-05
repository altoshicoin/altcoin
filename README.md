<p align="center">
  <img src="https://altoshi.org/altoshi.png" width="180" alt="Altcoin Logo"/>
</p>

<p align="center">
  <a href="https://github.com/altoshicoin/altcoin/releases">
    <img src="https://img.shields.io/github/v/release/altoshicoin/altcoin?label=Altcoin%20Core&color=blue"/>
  </a>
  <a href="https://opensource.org/licenses/MIT">
    <img src="https://img.shields.io/badge/license-MIT-green.svg"/>
  </a>
</p>

---

> ⚠️ **Altcoin NG1 is deprecated — NG2 mainnet coming soon**
>
> NG1 (the current chain) is now frozen as a **prelaunch / experimental chain**.
> It experienced extreme mining centralization (~96% of coins mined by a single miner)
> and early technical issues (stuck SegWit-style transactions).  
> We are preparing **Altcoin NG2**, a fresh mainnet with a new genesis, fixed consensus
> parameters, and a fairer launch. NG1 binaries and chain are kept only for testing.
>
> See the full transition notice in the Releases section.

---


# **Altcoin Core v2.0.0 (NG1 Mainnet)**

Altcoin (Altoshi Coin / **ALT**) is a Litecoin-family Proof-of-Work blockchain rebooted under a clean new-genesis mainnet (NG1), upgraded networking rules, modernized P2P behavior, and improved mining compatibility.  

Altoshi Coin (ALT) is a proof-of-work cryptocurrency focused on *fair distribution*, *open-source development*, and a *strong mining ecosystem*.
At its core, Altoshi Coin is about utility and community. It’s a clean foundation for learning, building, and iterating: from running nodes and mining to exploring transactions, testing wallets, and shaping a broader ecosystem over time. The slogan captures the vibe, but the goal is serious: a resilient, understandable PoW network with clear monetary rules, predictable issuance, and the kind of operational transparency that lets builders and users participate confidently. 

---

## **🔹 Technical Specs**

- **Coin name:** Altoshi Coin  
- **Ticker:** ALT  
- **Algorithm:** Scrypt (Proof-of-Work)  
- **Total Supply:** 88,000,000 ALT  
- **Block Reward:** 52.38095238 ALT  
- **Block Time:** 2.5 minutes (`nPowTargetSpacing = 2.5 * 60`)  
- **Halving Interval:** Every 840,000 blocks  
- **Premine:** 680.95238094 ALT → ~0.0007738% of 88,000,000  
- **Coinbase Maturity:** 100 blocks  
- **Target Timespan:** 84 hours  
- **Address Format:** Bech32 + MWEB (Litecoin-style, plus legacy support)  
- **P2P Port:** `11555`  
- **RPC Port:** `11433`  
- **Bootstrap Node:**  
  `addnode=node1.altoshi.org:11555`

---

## **🚀 Key Features**

- **New-Genesis Mainnet (NG1)**  
  Fresh chain with, consistent parameters, and predictable emission.

- **Improved P2P Sync (Fix B)**  
  Nodes no longer ignore `GETHEADERS` during initial block download (IBD).  
  New nodes can connect to a NG1 peer and synchronize normally.

- **Miner Compatibility Patch**  
  `getblocktemplate` supports miners that send `{"rules":["segwit"]}` only.  
  The node automatically handles the required MWEB rules internally, so modern Scrypt miners that speak Litecoin-style GBT work without patches.

- **Modern Feature Set**  
  Based on a Litecoin/Bitcoin 0.21 codebase with SegWit and MWEB support.

- **Updated Default Ports**  
  - P2P: `11555`  
  - RPC: `11433`  

---

## **📦 Downloads**

Precompiled binaries for Linux (x86_64) and Windows (x64) are available here:

👉 **https://github.com/altoshicoin/altcoin/releases/latest**

Each release includes:

- `altcoind` / `altcoin-qt`  
- `altcoin-cli`, `altcoin-tx`, `altcoin-wallet`  
- Archive files (`.tar.gz` / `.zip`)  
- SHA256SUMS files  
- GPG `.asc` signatures

---

## **🔧 Quick Start (Linux Node)**

Create a minimal config, e.g. `~/.altcoin/altcoin.conf`:

```conf
server=1
rpcuser=altuser
rpcpassword=strongpassword_here
rpcallowip=127.0.0.1
rpcbind=127.0.0.1
rpcport=11433

listen=1
port=11555

addnode=node1.altoshi.org:11555
txindex=0
```
Start the daemon:

```bash
./altcoind -daemon
```

Check sync status:

```bash
./altcoin-cli getblockchaininfo
```

---

## **🪟 Quick Start (Windows Node)**

1. Download the **Windows** archive from the latest release.
2. Extract it (e.g. `C:\Altcoin\` or similar).
3. Run `altcoin-qt.exe` for the GUI wallet, or `altcoind.exe` for daemon mode.
4. Altcoin will create a data directory, typically:
   `%APPDATA%\Altcoin\`
5. Create or edit `%APPDATA%\Altcoin\altcoin.conf` with similar contents:

```conf
server=1
rpcuser=altuser
rpcpassword=strongpassword_here
rpcallowip=127.0.0.1
rpcbind=127.0.0.1
rpcport=11433

listen=1
port=11555

addnode=node1.altoshi.org:11555
txindex=0
```

---

## **💻 Solo CPU Mining**

Altcoin uses **Scrypt**, compatible with standard Litecoin-style miners.

Example using `cpuminer-multi`:

```bash
./cpuminer -a scrypt \
  -o http://127.0.0.1:11433 \
  -u altuser -p strongpassword_here \
  --no-stratum \
  --coinbase-addr=YOUR_ALT_ADDRESS
```

### Advanced: `allowminingduringibd`

For solo miners or testing, you can allow mining during IBD:

```bash
./altcoind -conf=/path/to/altcoin.conf \
           -datadir=/path/to/altcoin-data \
           -allowminingduringibd=1
```

> ⚠ **Advanced option:** recommended only if you understand the risks of mining while not fully synced (potential reorgs / orphan blocks).

---

## **🏊 Mining Pools (Template Only)**

Altcoin supports standard Scrypt Stratum mining. A typical command pattern is:

```bash
cgminer -o stratum+tcp://yourpool.com:3333 \
        -u YOUR_ALT_ADDRESS \
        -p x \
        --scrypt
```

Pool operators should:

* Point their pool daemon to a fully synced Altcoin node (RPC `11433`, P2P `11555`)
* Use `algo = scrypt` in their pool configuration
* Configure `addnode=node1.altoshi.org:11555` (or another trusted NG1 peer)

> ℹ No official or endorsed pools are listed yet.
> Independent pool operators may contact the project to be listed in future docs.

---

## **🔐 Verification**

Verify SHA256 checksums (Linux):

```bash
sha256sum -c SHA256SUMS-linux-x86_64.txt
```

Verify signatures (after importing the Altcoin release key):

```bash
gpg --verify SHA256SUMS-linux-x86_64.txt.asc SHA256SUMS-linux-x86_64.txt
gpg --verify SHA256SUMS-win64-v2.0.0.txt.asc SHA256SUMS-win64-v2.0.0.txt
```

---

## **🧩 Source Code & Contributions**

Source code:
[https://github.com/altoshicoin/altcoin](https://github.com/altoshicoin/altcoin)

Contributions are welcome:

* Core protocol & consensus
* Wallet and GUI improvements
* Explorers, pool software integration
* Documentation and examples

Open issues and pull requests are appreciated.

---

## **🌐 Project Website**

Guides, explorer links, and ecosystem updates:
**[https://altoshi.org/](https://altoshi.org/)**

---

## **⚖️ License**

Altcoin Core is open-source software licensed under the **MIT License**.
See the `LICENSE` file for full details.

