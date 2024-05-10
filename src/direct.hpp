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

#include "openfhe/pke/cryptocontext-ser.h"
#include "openfhe/core/utils/serial.h"
#include "openfhe/pke/key/publickey.h"

enum SerialMode
{
    BINARY = 0,
    JSON = 1,
};

namespace openfhe_rs_dev
{
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
    using PublicKeyImpl = lbcrypto::PublicKeyImpl<lbcrypto::DCRTPoly>;
    using PrivateKeyImpl = lbcrypto::PrivateKeyImpl<lbcrypto::DCRTPoly>;
    using PlaintextImpl = lbcrypto::PlaintextImpl;
    using CiphertextImpl = lbcrypto::CiphertextImpl<lbcrypto::DCRTPoly>;
    using DecryptResult = lbcrypto::DecryptResult;
    using DCRTPolyParams = lbcrypto::DCRTPoly::Params;
    struct ComplexPair;
    using VectorOfComplexNumbers = std::vector<std::complex<double>>; // TODO: Think about vector of opaque C++ type
    using ::SerialMode;

    class PublicKeyDCRTPoly final
    {
    private:
        std::shared_ptr<PublicKeyImpl> m_publicKey;

    public:
        friend bool SerializePublicKeyToFile(const std::string& publicKeyLocation, const PublicKeyDCRTPoly& publicKey, const SerialMode serialMode);
        friend bool DeserializePublicKeyFromFile(const std::string& publicKeyLocation, PublicKeyDCRTPoly& publicKey, const SerialMode serialMode);
        // TODO: think about all special functions of class
        explicit PublicKeyDCRTPoly()
            : m_publicKey(std::make_shared<PublicKeyImpl>())
        { }
    };

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

    class Plaintext final
    {
    private:
        std::shared_ptr<PlaintextImpl> m_plaintext;

    public:
        // TODO: think about all special functions of class
        explicit Plaintext() = default;
        explicit Plaintext(std::shared_ptr<PlaintextImpl> plaintext)
            : m_plaintext(plaintext)
        { }
        Plaintext& operator=(std::shared_ptr<PlaintextImpl> plaintext)
        {
            m_plaintext = plaintext;
            return *this;
        }
        std::shared_ptr<PlaintextImpl> GetPlainText() const
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

    class CiphertextDCRTPoly final
    {
    private:
        std::shared_ptr<CiphertextImpl> m_ciphertext;

    public:
        friend bool SerializeCiphertextToFile(const std::string& ciphertextLocation, const CiphertextDCRTPoly& ciphertext, const SerialMode serialMode);
        friend bool DeserializeCiphertextFromFile(const std::string& ciphertextLocation, CiphertextDCRTPoly& ciphertext, const SerialMode serialMode);
        // TODO: think about all special functions of class
        explicit CiphertextDCRTPoly()
            : m_ciphertext(std::make_shared<CiphertextImpl>())
        { }
        explicit CiphertextDCRTPoly(std::shared_ptr<CiphertextImpl> ciphertext)
            : m_ciphertext(ciphertext)
        { }
        std::shared_ptr<CiphertextImpl> GetCipherText() const
        {
            return m_ciphertext;
        }
        // TODO: implement necessary member functions
    };

    class CryptoContextDCRTPoly final
    {
    private:
        std::shared_ptr<lbcrypto::CryptoContextImpl<lbcrypto::DCRTPoly>> m_cryptoContextImplSharedPtr;

    public:
        friend bool SerializeCryptoContextToFile(const std::string& ccLocation, const CryptoContextDCRTPoly& cryptoContext, const SerialMode serialMode);
        friend bool DeserializeCryptoContextFromFile(const std::string& ccLocation, CryptoContextDCRTPoly& cryptoContext, const SerialMode serialMode);
        friend bool SerializeEvalMultKeyToFile(const std::string& multKeyLocation, const CryptoContextDCRTPoly& cryptoContext, const SerialMode serialMode);
        friend bool SerializeEvalSumKeyToFile(const std::string& sumKeyLocation, const CryptoContextDCRTPoly& cryptoContext, const SerialMode serialMode);
        friend bool SerializeEvalAutomorphismKeyToFile(const std::string& automorphismKeyLocation, const CryptoContextDCRTPoly& cryptoContext, const SerialMode serialMode);

        // TODO: think about all special functions of class
        // TODO: about nullptr check in member functions
        explicit CryptoContextDCRTPoly() = default;
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
        std::unique_ptr<CiphertextDCRTPoly> EvalAdd(std::shared_ptr<CiphertextImpl> ciphertext1, std::shared_ptr<CiphertextImpl> ciphertext2) const
        {
            return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalAdd(ciphertext1, ciphertext2));
        }
        std::unique_ptr<CiphertextDCRTPoly> EvalSub(std::shared_ptr<CiphertextImpl> ciphertext1, std::shared_ptr<CiphertextImpl> ciphertext2) const
        {
            return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalSub(ciphertext1, ciphertext2));
        }
        std::unique_ptr<CiphertextDCRTPoly> EvalMult(std::shared_ptr<CiphertextImpl> ciphertext1, std::shared_ptr<CiphertextImpl> ciphertext2) const
        {
            return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalMult(ciphertext1, ciphertext2));
        }
        std::unique_ptr<CiphertextDCRTPoly> EvalMultByConst(std::shared_ptr<CiphertextImpl> ciphertext, const double constant) const
        {
            return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalMult(ciphertext, constant));
        }
        std::unique_ptr<CiphertextDCRTPoly> EvalRotate(std::shared_ptr<CiphertextImpl> ciphertext, const int32_t index) const
        {
            return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalRotate(ciphertext, index));
        }
        std::unique_ptr<CiphertextDCRTPoly> EvalChebyshevSeries(std::shared_ptr<CiphertextImpl> ciphertext, const std::vector<double>& coefficients,
                                                                const double a, const double b) const
        {
            return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalChebyshevSeries(ciphertext, coefficients, a, b));
        }
        std::unique_ptr<DecryptResult> Decrypt(const std::shared_ptr<lbcrypto::PrivateKeyImpl<lbcrypto::DCRTPoly>> privateKey,
                                               std::shared_ptr<CiphertextImpl> ciphertext, Plaintext& plaintext) const
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
        std::unique_ptr<Plaintext> MakeCKKSPackedPlaintextByVectorOfComplexNumbers(const std::vector<std::complex<double>>& value, const size_t scaleDeg, const uint32_t level,
                                                                                   const std::shared_ptr<DCRTPolyParams> params, const uint32_t slots) const
                                                                                   // scaleDeg = 1, level = 0, params = nullptr, slots = 0
        {
            return std::make_unique<Plaintext>(m_cryptoContextImplSharedPtr->MakeCKKSPackedPlaintext(value, scaleDeg, level, params, slots));
        }
        std::unique_ptr<CiphertextDCRTPoly> EvalPoly(std::shared_ptr<CiphertextImpl> ciphertext, const std::vector<double>& coefficients) const
        {
            return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalPoly(ciphertext, coefficients));
        }
    };

    bool SerializeCryptoContextToFile(const std::string& ccLocation, const CryptoContextDCRTPoly& cryptoContext, const SerialMode serialMode);
    bool DeserializeCryptoContextFromFile(const std::string& ccLocation, CryptoContextDCRTPoly& cryptoContext, const SerialMode serialMode);
    bool SerializeEvalMultKeyToFile(const std::string& multKeyLocation, const CryptoContextDCRTPoly& cryptoContext, const SerialMode serialMode);
    bool SerializeEvalMultKeyByIdToFile(const std::string& multKeyLocation, const SerialMode serialMode, const std::string& id);
    bool DeserializeEvalMultKeyFromFile(const std::string& multKeyLocation, const SerialMode serialMode);
    bool SerializeEvalSumKeyToFile(const std::string& sumKeyLocation, const CryptoContextDCRTPoly& cryptoContext, const SerialMode serialMode);
    bool SerializeEvalSumKeyByIdToFile(const std::string& sumKeyLocation, const SerialMode serialMode, const std::string& id);
    bool DeserializeEvalSumKeyFromFile(const std::string& sumKeyLocation, const SerialMode serialMode);
    bool SerializeEvalAutomorphismKeyToFile(const std::string& automorphismKeyLocation, const CryptoContextDCRTPoly& cryptoContext, const SerialMode serialMode);
    bool SerializeEvalAutomorphismKeyByIdToFile(const std::string& automorphismKeyLocation, const SerialMode serialMode, const std::string& id);
    bool DeserializeEvalAutomorphismKeyFromFile(const std::string& automorphismKeyLocation, const SerialMode serialMode);
    bool SerializeCiphertextToFile(const std::string& ciphertextLocation, const CiphertextDCRTPoly& ciphertext, const SerialMode serialMode);
    bool DeserializeCiphertextFromFile(const std::string& ciphertextLocation, CiphertextDCRTPoly& ciphertext, const SerialMode serialMode);
    bool SerializePublicKeyToFile(const std::string& publicKeyLocation, const PublicKeyDCRTPoly& publicKey, const SerialMode serialMode);
    bool DeserializePublicKeyFromFile(const std::string& publicKeyLocation, PublicKeyDCRTPoly& publicKey, const SerialMode serialMode);

    std::unique_ptr<VectorOfComplexNumbers> GenVectorOfComplexNumbers(const std::vector<ComplexPair>& vals);
    std::unique_ptr<Params> GetParamsByScheme(const SCHEME scheme);
    std::unique_ptr<Params> GetParamsByVectorOfString(const std::vector<std::string>& vals);
    std::unique_ptr<ParamsBFVRNS> GetParamsBFVRNS();
    std::unique_ptr<ParamsBFVRNS> GetParamsBFVRNSbyVectorOfString(const std::vector<std::string>& vals);
    std::unique_ptr<ParamsBGVRNS> GetParamsBGVRNS();
    std::unique_ptr<ParamsBGVRNS> GetParamsBGVRNSbyVectorOfString(const std::vector<std::string>& vals);
    std::unique_ptr<ParamsCKKSRNS> GetParamsCKKSRNS();
    std::unique_ptr<ParamsCKKSRNS> GetParamsCKKSRNSbyVectorOfString(const std::vector<std::string>& vals);
    std::unique_ptr<Plaintext> GenEmptyPlainText();
    std::unique_ptr<CryptoContextDCRTPoly> GenEmptyCryptoContext();
    std::unique_ptr<CryptoContextDCRTPoly> GenCryptoContextByParamsBFVRNS(const ParamsBFVRNS& params);
    std::unique_ptr<CryptoContextDCRTPoly> GenCryptoContextByParamsBGVRNS(const ParamsBGVRNS& params);
    std::unique_ptr<CryptoContextDCRTPoly> GenCryptoContextByParamsCKKSRNS(const ParamsCKKSRNS& params);
    std::unique_ptr<PublicKeyDCRTPoly> GenDefaultConstructedPublicKey();
    std::unique_ptr<CiphertextDCRTPoly> GenDefaultConstructedCiphertext();
} // openfhe_rs_dev
