{
  #source : https://nixcademy.com/posts/cpp-with-nix-in-2023-part-1-shell/
  description = "Nix flake for socialNetwork";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-parts.url = "github:hercules-ci/flake-parts";
  };

  outputs = inputs@{ flake-parts, ... }:
    flake-parts.lib.mkFlake { inherit inputs; } {
      systems = [
        "x86_64-linux" "aarch64-darwin"
      ];
      perSystem = { config, self', inputs', pkgs, system, ... }: {
        devShells.default = pkgs.mkShell {
          packages = with pkgs; [
            gcc
            emscripten
            cmake
            thrift
            mongoc
            cyrus_sasl
            libamqpcpp
            nlohmann_json
            openssl
            libmemcached
            libevent
            yaml-cpp
            boost
            nodejs_22
          ];

          # Force CMake to use shared libraries for Boost
          shellHook = ''
            export Boost_USE_STATIC_LIBS=OFF
            export MEMCACHED_USE_EXTERNAL_LIBRARY=OFF
              # emscripten utilise du cache
              # comme avec nix on authorise pas d'écrire dans le store
              # On met le cache dans un répertoire temporaire
              export EM_CACHE="$TMPDIR/emscripten_cache"
          '';
        };
      };
    };
}