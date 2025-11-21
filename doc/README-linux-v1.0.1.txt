ALTCOIN Core v1.0.1 (Linux)
===========================

Contents
--------
This folder contains prebuilt 64-bit Linux binaries:

  bin/altcoind      - Altcoin daemon (headless node)
  bin/altcoin-cli   - Command-line RPC client
  bin/altcoin-qt    - GUI wallet
  bin/altcoin-tx    - Raw transaction utility

  altcoin.conf.sample  - Example configuration file


Quick start (desktop GUI)
-------------------------
1. Extract the archive somewhere, for example:

     tar xzf altcoin-core-linux-v1.0.1.tar.gz
     cd altcoin-core-linux-v1.0.1

2. Create your data directory and copy the sample config:

     mkdir -p ~/.altcoin
     cp altcoin.conf.sample ~/.altcoin/altcoin.conf

3. Start the GUI wallet:

     ./bin/altcoin-qt

4. The node will connect to the Altcoin network and use:

   - P2P port: 11500
   - Bootstrap node: node1.altoshi.org:11500


Headless node (server mode)
---------------------------
To run a background node without the GUI:

1. Make sure you have a config in ~/.altcoin/altcoin.conf
   (you can start from altcoin.conf.sample).

2. Start the daemon:

     ./bin/altcoind -daemon

3. Use the CLI to talk to the node, for example:

     ./bin/altcoin-cli getblockcount
     ./bin/altcoin-cli getnetworkinfo


Solo mining / RPC
-----------------
For normal wallet use you do NOT need RPC.

If you want to use external miners (cpuminer, etc.):

- Edit ~/.altcoin/altcoin.conf
- Follow the "Advanced: RPC / solo mining" section in altcoin.conf.sample
  to generate an rpcauth line and allow only trusted IP ranges.
- Never expose the RPC port directly to the public internet.


Data locations
--------------
Default datadir:

  Linux:  ~/.altcoin

Config file:

  Linux:  ~/.altcoin/altcoin.conf

You can override the datadir with -datadir=... and config path with -conf=...
on the command line if needed.


Notes
-----
- Altcoin is a new chain. The sample config relaxes minimumchainwork and
  assumevalid so nodes do not get stuck waiting for a huge historical chain.
- The shipped binaries are intended for modern 64-bit Linux distributions.
  On some systems you may need to install additional runtime libraries
  (Qt, libevent, boost, etc.).
