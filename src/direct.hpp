#pragma once

#include <memory>
#include <sstream>
#include "rust/cxx.h" // rust::String

#include "openfhe/pke/scheme/gen-cryptocontext-params.h"
#include "openfhe/pke/scheme/bfvrns/gen-cryptocontext-bfvrns-params.h"
#include "openfhe/pke/scheme/bgvrns/gen-cryptocontext-bgvrns-params.h"
#include "openfhe/pke/scheme/ckksrns/gen-cryptocontext-ckksrns-params.h"

#include "openfhe/pke/gen-cryptocontext.h"
#include "openfhe/pke/scheme/bfvrns/gen-cryptocontext-bfvrns.h"
#include "openfhe/pke/scheme/bgvrns/gen-cryptocontext-bgvrns.h"
#include "openfhe/pke/scheme/ckksrns/gen-cryptocontext-ckksrns.h"

#include "openfhe/pke/scheme/scheme-id.h" // enums
#include "openfhe/core/lattice/constants-lattice.h" // enums
#include "openfhe/pke/constants-fwd.h" // enumss
#include "openfhe/core/lattice/stdlatticeparms.h" // enums
#include "openfhe/pke/key/keypair.h"
#include "openfhe/core/utils/inttypes.h"

#include "openfhe/pke/key/keypair.h"
#include "openfhe/pke/key/privatekey.h"
#include "openfhe/pke/key/publickey.h"

#include "openfhe/pke/ciphertext.h"
#include "openfhe/pke/encoding/plaintext.h"
#include "openfhe/pke/schemebase/decrypt-result.h"

namespace openfhe_rs_dev
{
    // Parameter related stuff
    using ParamsBFVRNS = lbcrypto::CCParams<lbcrypto::CryptoContextBFVRNS>;
    using ParamsBGVRNS = lbcrypto::CCParams<lbcrypto::CryptoContextBGVRNS>;
    using ParamsCKKSRNS = lbcrypto::CCParams<lbcrypto::CryptoContextCKKSRNS>;
    using Params = lbcrypto::Params;
    using SCHEME = lbcrypto::SCHEME;
    using SecretKeyDist = lbcrypto::SecretKeyDist;
    using ProxyReEncryptionMode = lbcrypto::ProxyReEncryptionMode;
    using MultipartyMode = lbcrypto::MultipartyMode;
    using ExecutionMode = lbcrypto::ExecutionMode;
    using DecryptionNoiseMode = lbcrypto::DecryptionNoiseMode;
    using KeySwitchTechnique = lbcrypto::KeySwitchTechnique;
    using ScalingTechnique = lbcrypto::ScalingTechnique;
    using SecurityLevel = lbcrypto::SecurityLevel;
    using EncryptionTechnique = lbcrypto::EncryptionTechnique;
    using MultiplicationTechnique = lbcrypto::MultiplicationTechnique;
    using COMPRESSION_LEVEL = lbcrypto::COMPRESSION_LEVEL;
    using PKESchemeFeature = lbcrypto::PKESchemeFeature;
    std::unique_ptr<Params> GetParamsByScheme(const SCHEME scheme)
    {
        return std::make_unique<Params>(scheme);
    }
    std::unique_ptr<Params> GetParamsByVectorOfString(const std::vector<std::string>& vals)
    {
        return std::make_unique<Params>(vals);
    }
    std::unique_ptr<ParamsBFVRNS> GetParamsBFVRNS()
    {
        return std::make_unique<ParamsBFVRNS>();
    }
    std::unique_ptr<ParamsBFVRNS> GetParamsBFVRNSbyVectorOfString(const std::vector<std::string>& vals)
    {
        return std::make_unique<ParamsBFVRNS>(vals);
    }
    std::unique_ptr<ParamsBGVRNS> GetParamsBGVRNS()
    {
        return std::make_unique<ParamsBGVRNS>();
    }
    std::unique_ptr<ParamsBGVRNS> GetParamsBGVRNSbyVectorOfString(const std::vector<std::string>& vals)
    {
        return std::make_unique<ParamsBGVRNS>(vals);
    }
    std::unique_ptr<ParamsCKKSRNS> GetParamsCKKSRNS()
    {
        return std::make_unique<ParamsCKKSRNS>();
    }
    std::unique_ptr<ParamsCKKSRNS> GetParamsCKKSRNSbyVectorOfString(const std::vector<std::string>& vals)
    {
        return std::make_unique<ParamsCKKSRNS>(vals);
    }

    using PublicKeyImpl = lbcrypto::PublicKeyImpl<lbcrypto::DCRTPoly>;
    using PrivateKeyImpl = lbcrypto::PrivateKeyImpl<lbcrypto::DCRTPoly>;

    class KeyPairDCRTPoly final
    {
    private:
        std::shared_ptr<PublicKeyImpl> m_publicKey;
        std::shared_ptr<PrivateKeyImpl> m_privateKey;

    public:
        // TODO: think about all special functions of class
        explicit KeyPairDCRTPoly(lbcrypto::KeyPair<lbcrypto::DCRTPoly> keyPair)
            : m_publicKey(keyPair.publicKey)
            , m_privateKey(keyPair.secretKey)
        { }
        std::shared_ptr<PublicKeyImpl> GetPublicKey() const
        {
            return m_publicKey;
        }
        std::shared_ptr<PrivateKeyImpl> GetPrivateKey() const
        {
            return m_privateKey;
        }
        // TODO: implement necessary member functions
    };

    using PlaintextImpl = lbcrypto::PlaintextImpl;
    class Plaintext final
    {
    private:
        std::shared_ptr<lbcrypto::PlaintextImpl> m_plaintext;

    public:
        // TODO: think about all special functions of class
        explicit Plaintext() = default;
        explicit Plaintext(std::shared_ptr<lbcrypto::PlaintextImpl> plaintext)
            : m_plaintext(plaintext)
        { }
        Plaintext& operator=(std::shared_ptr<lbcrypto::PlaintextImpl> plaintext)
        {
            m_plaintext = plaintext;
            return *this;
        }
        std::shared_ptr<lbcrypto::PlaintextImpl> GetPlainText() const
        {
            return m_plaintext;
        }
        void SetLength(const size_t newSize) const
        {
            if (m_plaintext)
            {
                m_plaintext->SetLength(newSize);
            }
        }
        double GetLogPrecision() const
        {
            return m_plaintext->GetLogPrecision();
        }
        rust::String GetString() const
        {
            if (m_plaintext)
            {
                std::stringstream stream;
                stream << *m_plaintext;
                return rust::String(stream.str());
            }
            return rust::String();
        }
        // TODO: implement necessary member functions
    };

    std::unique_ptr<Plaintext> GenEmptyPlainText()
    {
        return std::make_unique<Plaintext>();
    }

    using CiphertextImpl = lbcrypto::CiphertextImpl<lbcrypto::DCRTPoly>;
    class CiphertextDCRTPoly final
    {
    private:
        std::shared_ptr<lbcrypto::CiphertextImpl<lbcrypto::DCRTPoly>> m_ciphertext;

    public:
        // TODO: think about all special functions of class
        explicit CiphertextDCRTPoly(std::shared_ptr<lbcrypto::CiphertextImpl<lbcrypto::DCRTPoly>> ciphertext)
            : m_ciphertext(ciphertext)
        { }
        std::shared_ptr<lbcrypto::CiphertextImpl<lbcrypto::DCRTPoly>> GetCipherText() const
        {
            return m_ciphertext;
        }
        // TODO: implement necessary member functions
    };

    using DecryptResult = lbcrypto::DecryptResult;
    using DCRTPolyParams = lbcrypto::DCRTPoly::Params;
    class CryptoContextDCRTPoly final
    {
    private:
        std::shared_ptr<lbcrypto::CryptoContextImpl<lbcrypto::DCRTPoly>> m_cryptoContextImplSharedPtr;

    public:
        // TODO: think about all special functions of class
        explicit CryptoContextDCRTPoly(const ParamsBFVRNS& params)
            : m_cryptoContextImplSharedPtr(lbcrypto::GenCryptoContext(params))
        { }
        explicit CryptoContextDCRTPoly(const ParamsBGVRNS& params)
            : m_cryptoContextImplSharedPtr(lbcrypto::GenCryptoContext(params))
        { }
        explicit CryptoContextDCRTPoly(const ParamsCKKSRNS& params)
            : m_cryptoContextImplSharedPtr(lbcrypto::GenCryptoContext(params))
        { }
        void Enable(const PKESchemeFeature feature) const
        {
            m_cryptoContextImplSharedPtr->Enable(feature);
        }
        std::unique_ptr<KeyPairDCRTPoly> KeyGen() const
        {
            return std::make_unique<KeyPairDCRTPoly>(m_cryptoContextImplSharedPtr->KeyGen());
        }
        void EvalMultKeyGen(const std::shared_ptr<lbcrypto::PrivateKeyImpl<lbcrypto::DCRTPoly>> key) const
        {
            m_cryptoContextImplSharedPtr->EvalMultKeyGen(key);
        }
        void EvalRotateKeyGen(const std::shared_ptr<lbcrypto::PrivateKeyImpl<lbcrypto::DCRTPoly>> privateKey, const std::vector<int32_t>& indexList,
							                const std::shared_ptr<lbcrypto::PublicKeyImpl<lbcrypto::DCRTPoly>> publicKey) const // publicKey = nullptr in original. Rust don't support default args.
        {
            m_cryptoContextImplSharedPtr->EvalRotateKeyGen(privateKey, indexList, publicKey);
        }
        std::unique_ptr<Plaintext> MakePackedPlaintext(const std::vector<int64_t>& value, const size_t noiseScaleDeg, const uint32_t level) const // noiseScaleDeg = 1, level = 0
        {
            return std::make_unique<Plaintext>(m_cryptoContextImplSharedPtr->MakePackedPlaintext(value, noiseScaleDeg, level));
        }
        std::unique_ptr<CiphertextDCRTPoly> Encrypt(const std::shared_ptr<lbcrypto::PublicKeyImpl<lbcrypto::DCRTPoly>> publicKey, std::shared_ptr<lbcrypto::PlaintextImpl> plaintext) const
        {
            return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->Encrypt(publicKey, plaintext));
        }
        std::unique_ptr<CiphertextDCRTPoly> EvalAdd(std::shared_ptr<lbcrypto::CiphertextImpl<lbcrypto::DCRTPoly>> ciphertext1,
                                                    std::shared_ptr<lbcrypto::CiphertextImpl<lbcrypto::DCRTPoly>> ciphertext2) const
        {
            return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalAdd(ciphertext1, ciphertext2));
        }
        std::unique_ptr<CiphertextDCRTPoly> EvalSub(std::shared_ptr<lbcrypto::CiphertextImpl<lbcrypto::DCRTPoly>> ciphertext1,
                                                    std::shared_ptr<lbcrypto::CiphertextImpl<lbcrypto::DCRTPoly>> ciphertext2) const
        {
            return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalSub(ciphertext1, ciphertext2));
        }

        std::unique_ptr<CiphertextDCRTPoly> EvalMult(std::shared_ptr<lbcrypto::CiphertextImpl<lbcrypto::DCRTPoly>> ciphertext1,
                                                     std::shared_ptr<lbcrypto::CiphertextImpl<lbcrypto::DCRTPoly>> ciphertext2) const
        {
            return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalMult(ciphertext1, ciphertext2));
        }
        std::unique_ptr<CiphertextDCRTPoly> EvalMultByConst(std::shared_ptr<lbcrypto::CiphertextImpl<lbcrypto::DCRTPoly>> ciphertext, const double constant) const
        {
            return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalMult(ciphertext, constant));
        }
        std::unique_ptr<CiphertextDCRTPoly> EvalRotate(std::shared_ptr<lbcrypto::CiphertextImpl<lbcrypto::DCRTPoly>> ciphertext, const int32_t index) const
        {
            return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalRotate(ciphertext, index));
        }
        std::unique_ptr<DecryptResult> Decrypt(const std::shared_ptr<lbcrypto::PrivateKeyImpl<lbcrypto::DCRTPoly>> privateKey,
                                               std::shared_ptr<lbcrypto::CiphertextImpl<lbcrypto::DCRTPoly>> ciphertext, Plaintext& plaintext) const
        {
            std::shared_ptr<lbcrypto::PlaintextImpl> res;
            std::unique_ptr<DecryptResult> result = std::make_unique<DecryptResult>(m_cryptoContextImplSharedPtr->Decrypt(privateKey, ciphertext, &res));
            plaintext = res;
            return result;
        }
        uint32_t GetRingDimension() const
        {
            return m_cryptoContextImplSharedPtr->GetRingDimension();
        }
        std::unique_ptr<Plaintext> MakeCKKSPackedPlaintext(const std::vector<double>& value, const size_t scaleDeg, const uint32_t level,
                                                           const std::shared_ptr<DCRTPolyParams> params, const uint32_t slots) const
                                                           // scaleDeg = 1, level = 0, params = nullptr, slots = 0
        {
            return std::make_unique<Plaintext>(m_cryptoContextImplSharedPtr->MakeCKKSPackedPlaintext(value, scaleDeg, level, params, slots));
        }
    };

    std::unique_ptr<CryptoContextDCRTPoly> GenCryptoContextByParamsBFVRNS(const ParamsBFVRNS& params)
    {
        return std::make_unique<CryptoContextDCRTPoly>(params);
    }
    std::unique_ptr<CryptoContextDCRTPoly> GenCryptoContextByParamsBGVRNS(const ParamsBGVRNS& params)
    {
        return std::make_unique<CryptoContextDCRTPoly>(params);
    }
    std::unique_ptr<CryptoContextDCRTPoly> GenCryptoContextByParamsCKKSRNS(const ParamsCKKSRNS& params)
    {
        return std::make_unique<CryptoContextDCRTPoly>(params);
    }
} // openfhe_rs_dev

