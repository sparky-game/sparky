import Layout from '@theme/Layout';
import BrowserOnly from '@docusaurus/BrowserOnly';
import HomepageHeader from '@site/src/components/HomepageHeader';
import HomepageFeatures from '@site/src/components/HomepageFeatures';
import HomepageCarousel from '@site/src/components/HomepageCarousel';

function Homepage() {
  return (
    <Layout>
      <HomepageHeader />
      <main>
        <HomepageCarousel />
        <HomepageFeatures />
      </main>
    </Layout>
  );
}

export default function Home() {
  return (
    <BrowserOnly>
      {() => <Homepage />}
    </BrowserOnly>
  );
}
