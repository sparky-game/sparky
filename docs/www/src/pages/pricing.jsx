import Layout from '@theme/Layout';
import BrowserOnly from '@docusaurus/BrowserOnly';

function PricingPage() {
  return (
    <Layout>
      <h1>Free as in freedom.</h1>
    </Layout>
  );
}

export default function Pricing() {
  return (
    <BrowserOnly>
      {() => <PricingPage />}
    </BrowserOnly>
  );
}
